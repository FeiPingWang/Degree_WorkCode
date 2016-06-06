#include "mainwindow.h"
#include "ui_mainwindow.h"

int FlagCan0 = 1;   //CAN线路标志变量

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    DateTime = new QTimer(this);     //显示系统实时时间
    connect(DateTime, SIGNAL(timeout()), this, SLOT(timeupdate()));
    DateTime->start(1000);

    /*编辑框过滤器*/

}

MainWindow::~MainWindow()
{
    delete DateTime;
    delete ui;
}

/*显示系统实时时间*/
void MainWindow::timeupdate()
{
    QDateTime DataTime = QDateTime::currentDateTime();
    QString str = DataTime.toString("yyyy-MM-dd hh:mm:ss");
    ui->labelTime->setText(str);
}

/*退出函数*/
void MainWindow::on_actQuit_triggered()
{
    QMessageBox message(QMessageBox::Warning,"Warnig","Do you want to quit?",QMessageBox::Yes|QMessageBox::No,NULL);
    if(message.exec()==QMessageBox::Yes)
        close();
}

/*开启CAN0/1总线函数*/
void MainWindow::on_actRun_triggered()
{
    m_strBit = "500000";

    /*开启CAN0*/
    QStringList list;  //开启can0
    list << "can0" << "stop";
    QProcess *process1 = new QProcess(this);
    process1 -> execute("canconfig",list);   //1.配置第一步

    list.clear();
    list << "can0" << "bitrate" << m_strBit << "ctrlmode" << "triple-sampling" \
         << "on" << "listen-only" << "off" << "loopback" << "off";

    QProcess *process2 = new QProcess(this);
    process2-> execute("canconfig",list);

    list.clear();
    list << "can0" << "start";
    QProcess *process3 = new QProcess(this);
    process3-> execute("canconfig",list);  //完成配置
  /*--------------------------------------------------------------*/
    /*开启can1*/
    QStringList list1;  //开启can1
    list1 << "can1" << "stop";
    QProcess *process4 = new QProcess(this);
    process4 -> execute("canconfig",list1);   //1.配置第一步

    list1.clear();
    list1 << "can1" << "bitrate" << m_strBit << "ctrlmode" << "triple-sampling" \
         << "on" << "listen-only" << "off" << "loopback" << "off";

    QProcess *process5 = new QProcess(this);
    process5-> execute("canconfig",list1);

    list1.clear();
    list1 << "can1" << "start";
    QProcess *process6 = new QProcess(this);
    process6-> execute("canconfig",list1);  //完成配置

    /* 接收CAN消息函数 */
    m_cptr0 = {"candump","can0",""};
    m_threadRecv0 = new ThreadRec(2,m_cptr0);
    connect(m_threadRecv0,SIGNAL(mesRecv(QString)), this, SLOT(ShowCanMsg1(QString)));
    m_threadRecv0->start();

    m_cptr1 = {"candump","can1",""};
    m_threadRecv1 = new ThreadRec1(2,m_cptr1);
    connect(m_threadRecv1,SIGNAL(mesRecv1(QString)), this, SLOT(ShowCanMsg2(QString)));
    m_threadRecv1->start();
    QMessageBox::warning(this,("warning"),QString("Success start CAN"));
}

/* 停止函数 */
void MainWindow::on_actStop_triggered()
{
    QStringList list;
    list << "can0" << "stop";
    QProcess* process1;
    process1 = new QProcess();
    process1->execute("canconfig", list);

    list.clear();
    list << "can1" << "stop";
    QProcess* process2;
    process2 = new QProcess();
    process2->execute("canconfig", list);

    m_threadRecv0->stop();          //关闭接收消息线程
    m_threadRecv1->stop();

}

/* 发送函数 */
void MainWindow::on_pBSend_clicked()  //成功
{
    QProcess *process1 = new QProcess(this);
    QString str,str1;
    QStringList ListControl;
    int fre = 0,high=0,low=0,fre1=0;
    float Zq = 0.0;
    bool ok;

    if(FlagCan0 == 1)
    {
        str = "can0";
        ui->lb_canshow->setText("can0");     //标签
    }
    else
    {
        str = "can1";
        ui->lb_canshow->setText("can1");
    }
    ListControl.clear();

    str1 = ui->lEZkb->text();  //获取占空比的参数
    ListControl << str1;

    str1 = ui->lEPl->text();   //获取频率的参数
    if(ui->cBHz->currentText() == "HZ")
    {
        fre = str1.toInt(&ok,10);
        fre1 = 100000/fre;           //与单片机公式转化
        high = fre1 / 256;          //第2字节（高位）
        low = fre1 % 256;          //第3字节（低位）
        ListControl << QString::number(high) << QString::number(low);
    }

    else if(ui->cBHz->currentText() == "KHZ")
    {
        fre = str1.toInt(&ok,10);
        fre1 = fre1 * 1000;
        fre1 = 100000/fre;           //与单片机公式转化
        high = fre1 / 256;          //第2字节（高位）
        low = fre1 % 256;          //第3字节（低位）
        ListControl << QString::number(high) << QString::number(low);
    }

    str1 = ui->lEZq->text();             //获取周期个数的参数
    Zq = str1.toFloat();
    Zq = Zq / (float)fre *1000;        //单位为ms
    high = (int)Zq /256;              //第4字节（高位）
    low = (int)Zq % 256;             //第5字节（低位）
    ListControl << QString::number(high) << QString::number(low);

    str1 = ui->lEJg->text();         //获取两串信号之间的间隔参数
    ListControl << str1;            //第6字节

    str1 = ui->lECjcs->text();      //获取刺激次数
    ListControl << str1;            //第7字节

    str1 = ui->lEYcsj->text();      //获取延时时间
    ListControl << str1;            //第8字节

    ListControl.insert(0,"0x010");
    ListControl.insert(0,"-i");
    ListControl.insert(0,str);
    process1->execute("cansend", ListControl);
}
