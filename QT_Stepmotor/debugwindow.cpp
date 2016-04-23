#include "debugwindow.h"
#include "ui_debugwindow.h"

DebugWindow::DebugWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DebugWindow)
{
    ui->setupUi(this);

    m_cptr = {"candump","can0",""};      //开启收取消息线程
    m_threadRecv0 = new ThreadRec(2,m_cptr);
    connect(m_threadRecv0,SIGNAL(mesRecv(QString)), this, SLOT(ShowCanMsg(QString)));
    m_threadRecv0->start();
}

DebugWindow::~DebugWindow(){
    delete ui;
}

/* 退出调试，关闭接收消息线程(暂定) */
void DebugWindow::on_D_pB_Exit_clicked()
{
    QProcess* process1;
    QStringList list;
    list << ui->D_lb_router->text() << "stop";

    process1 = new QProcess();
    process1->execute("canconfig", list);
    m_threadRecv0->stop();           //关闭接收消息线程（要先start，否则会导致异常退出）
    this->close();
}

/*** 状态改变函数 ****/
void DebugWindow::cbStateChanged(){     //当CAN的参数改变时，重新配置接受消息线程
    m_cptr[0] = "candump";
    m_cptr[1] = "can0";
    m_cptr[2] = " ";
    m_threadRecv0 = new ThreadRec(2,m_cptr);
    connect(m_threadRecv0,SIGNAL(mesRecv(QString)), this, SLOT(ShowCanMsg(QString)));
    m_threadRecv0->start();
}

/* 接收消息显示框1 */
void DebugWindow::ShowCanMsg(QString str)
{
    if (ui->D_tB_ShowMessage->toPlainText().length() > 2000)
        ui->D_tB_ShowMessage->clear();
    m_strDisplay = m_strDisplay + str + "\n";
    ui->D_tB_ShowMessage->setText(m_strDisplay);
    QTextCursor cursor = ui->D_tB_ShowMessage->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->D_tB_ShowMessage->setTextCursor(cursor);
}

/* 设置实时显示 */
void DebugWindow::setDisLabel(QString router,QString mode,QString bitrate)
{
    ui->D_show_router->setText(router);
    ui->D_show_mode->setText(mode);
    ui->D_show_bitrate->setText(bitrate);
}

/* 调试发送函数 */
void DebugWindow::on_D_pB_Send_clicked()
{
    QProcess *processDsend = new QProcess(this);
    QStringList list;
    QString strTmp = ui->D_lE_Data->text();
    QStringList listData = strTmp.split(" ");
    for(int i = 0;i < listData.size();i++)
        list << listData[i];

    QString strId = ui->D_lE_Id->text();       //ID
    list.insert(0,strId);
    list.insert(0,"-i");
    list.insert(0,ui->D_show_router->text());  //can线路
    processDsend->execute("cansend", list);    //发送

#ifdef Print_DEBUG
   QTextStream cout(stdout,QIODevice::WriteOnly);
    for(int i=0;i<list.size();i++)
        cout << list[i]<<endl;
#endif
}
