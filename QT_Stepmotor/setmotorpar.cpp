#include "setmotorpar.h"
#include "ui_setmotorpar.h"

SetMotorPar::SetMotorPar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetMotorPar)
{
    ui->setupUi(this);
}

SetMotorPar::~SetMotorPar()
{
    delete ui;
}

/*退出设置步进电机界面*/
void SetMotorPar::on_pB_Eixt_clicked()
{
    this->close();
}

void SetMotorPar::on_pB_Confirm_clicked()
{
    QStringList list;
    int dirNum = 0,motorNum = 0;
    QString motor;
    QString dir;

    if(ui->cB_Mo_1->isTristate()  == true)       //步进电机1
        motorNum = motorNum | 0x01;
    if(ui->cB_Mo_2->isTristate()  == true)       //步进电机2
        motorNum = motorNum | 0x02;

    if(ui->Dir_1->currentText() == "顺时针")    //步进电机方向
        dirNum = dirNum | 0x01;
    if(ui->Dir_2->currentText() == "顺时针")
        dirNum = dirNum & 0x02;

    motor = QString::number(motorNum,16);      //convert to QString
    dir = QString::number(dirNum,16);

#ifdef DEBUG
    cout << "motor" << motor << endl;
    cout << "dir" << dir << endl;
#endif

}
