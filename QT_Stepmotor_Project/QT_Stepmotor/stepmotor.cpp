#include "stepmotor.h"
#include "ui_stepmotor.h"

StepMotor::StepMotor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StepMotor)
{
    ui->setupUi(this);
    setcanpar = new SetCANPar(this);
    connect(setcanpar, SIGNAL(stateChanged()), this, SLOT(cbStateChanged()));

    DateTime = new QTimer(this);     //显示系统实时时间
    connect(DateTime, SIGNAL(timeout()), this, SLOT(timeupdate()));
    DateTime->start(1000);
}

StepMotor::~StepMotor()
{
    delete ui;
}

/**** can参数设置对话框显示函数 ****/
void StepMotor::on_pB_Can_Set_clicked()     //successful
{
    setcanpar->show();
}

/**** can参数设置对话框关闭 ****/
void StepMotor::on_action_Exit_triggered()  //Successful
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

/*状态改变函数*/
void StepMotor::cbStateChanged()  //当CAN的参数改变时，重新配置接受消息线程
{
    m_cptr[0] = "candump";
    m_cptr[1] = "can0";
    m_cptr[2] = " ";
    m_threadRecv0 = new ThreadRec(2,m_cptr);
    connect(m_threadRecv0,SIGNAL(mesRecv(QString)), this, SLOT(ShowCanMsg(QString)));
    m_threadRecv0->start();
}
