#include "stepmotor.h"
#include "ui_stepmotor.h"

StepMotor::StepMotor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StepMotor)
{
    ui->setupUi(this);
    setcanpar = new SetCANPar(this);
}

StepMotor::~StepMotor()
{
    delete ui;
}

/**** can参数设置对话框显示函数 ****/
void StepMotor::on_pB_Can_Set_clicked()     //Unsuccessful
{
  //  QMessageBox::warning(this,("warning"),QString("Start can0 and can1 together?"),QMessageBox::Yes,QMessageBox::No);
    setcanpar->show();
}

/**** can参数设置对话框关闭 ****/
void StepMotor::on_action_Exit_triggered()  //Successful
{
    close();    //关闭
}
