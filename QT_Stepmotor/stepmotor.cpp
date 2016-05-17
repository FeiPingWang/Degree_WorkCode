#include "stepmotor.h"
#include "ui_stepmotor.h"

StepMotor::StepMotor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StepMotor)
{
    ui->setupUi(this);
    setcanpar = new SetCANPar(this);
    debugwindow = new DebugWindow(this);
    setMotorPar = new SetMotorPar(this);

    connect(setcanpar, SIGNAL(stateChanged()), debugwindow, SLOT(cbStateChanged()));     //receiver 为 debugwindow对象
    connect(setcanpar,SIGNAL(displySignal(QString,QString,QString)),debugwindow,SLOT(setDisLabel(QString,QString,QString)));
    connect(setMotorPar,SIGNAL(SendMotorPar(QStringList)),this,SLOT(getMotorPar(QStringList)));  //得到步进电机的设置数据发送
  //  connect(setcanpar,SIGNAL(displySignal(QString,QString,QString)l),this,SLOT(getCanPar(QString,QString,QString)));
    DateTime = new QTimer(this);         //显示系统实时时间
    connect(DateTime, SIGNAL(timeout()), this, SLOT(timeupdate()));
    DateTime->start(1000);
}

StepMotor::~StepMotor()
{
    delete ui;
}

/**** can参数设置对话框显示函数 ****/
void StepMotor::on_pB_Can_Set_clicked()
{
    setcanpar->show();
}

/**** can参数设置对话框关闭 ****/
void StepMotor::on_action_Exit_triggered()
{
    close();    //关闭
}

/*** 更新时间函数 ****/
void StepMotor::timeupdate()
{
    QDateTime DataTime = QDateTime::currentDateTime();
    QString str = DataTime.toString("yyyy-MM-dd hh:mm:ss");
    ui->lb_Time->setText(str);
}

/**** 停止函数 ****/
void StepMotor::on_action_Stop_triggered()
{
    QStringList list;
    QString can = setcanpar->getcB_Can();
#ifdef Print_DEBUG
    QTextStream cout(stdout,QIODevice::WriteOnly);
    cout << can <<endl;
#endif
    list << can << "stop";
}

void StepMotor::on_pushButton_clicked()
{
    debugwindow->show();
}

void StepMotor::on_pB_motor_set_clicked()
{
    setMotorPar->show();
}

/*发送控制步进电机信号（Debug）*/
void StepMotor::on_pB_Start_Debug_clicked()
{
    QProcess *processMotorSend = new QProcess(this);
    SendList.insert(0,"0x01");  //ID
    SendList.insert(0,"-i");
    SendList.insert(0,setcanpar->getcB_Can());      //CAN router
    processMotorSend->execute("cansend", SendList);     //发送
#ifdef Print_DEBUG
    QTextStream cout(stdout,QIODevice::WriteOnly);
    cout << "SendList" << endl;
    for(QStringList::iterator iter = SendList.begin();iter != SendList.end();iter++)
    {
        cout << *iter << " ";
    }
    cout << endl;
#endif
}

void StepMotor::getMotorPar(QStringList motorPar)
{
    SendList.clear();   //clear first
    for(QStringList::iterator iter = motorPar.begin();iter != motorPar.end();iter++)
    {
        QString s = *iter;
        SendList << s;      //保存到发送list中
    }
}
