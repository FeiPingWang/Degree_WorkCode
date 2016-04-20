#include "stepmotor.h"
#include "ui_stepmotor.h"
#include <QTextStream>
StepMotor::StepMotor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StepMotor)
{
    ui->setupUi(this);
    setcanpar = new SetCANPar(this);
    debugwindow = new DebugWindow(this);

    connect(setcanpar, SIGNAL(stateChanged()), debugwindow, SLOT(cbStateChanged())); //receiver 为 debugwindow对象
    connect(setcanpar,SIGNAL(displySignal(QString,QString,QString)),debugwindow,SLOT(setDisLabel(QString,QString,QString)));

    DateTime = new QTimer(this);      //显示系统实时时间
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
