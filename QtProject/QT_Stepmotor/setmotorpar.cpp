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
    QString Pwm;
    int Data2 = 0,Data3 = 0,Data4=0;

    int PwmNum = 0;
    if(ui->cB_Mo_1->isChecked()  == true)       //步进电机1
        motorNum = motorNum | 0x01;
    if(ui->cB_Mo_2->isChecked()  == true)       //步进电机2
        motorNum = motorNum | 0x02;

    if(ui->Dir_1->currentIndex() == 0)          //步进电机方向
        dirNum = dirNum | 0x01;
    if(ui->Dir_2->currentIndex() == 0)
        dirNum = dirNum | 0x02;

    motor = QString::number(motorNum,10);        //convert to QString
    dir = QString::number(dirNum,10);
    list << motor << dir;                       //data[0],data[1]
    Pwm = ui->lE_Horizon_Set->text();
    PwmNum = Pwm.toInt();                        //转换
    Data2 = PwmNum / 10000;
    Data3 = PwmNum % 10000/100;
    Data4 = PwmNum % 100;
    list << QString::number(Data2,10) << QString::number(Data3,10) << QString::number(Data4,10); //data[2,3,4]
    emit SendMotorPar(list);    //发送信号到主窗口

#ifdef Print_DEBUG
    QTextStream cout(stdout,QIODevice::WriteOnly);
   // cout << ui->Dir_1->currentIndex() << endl;
    cout<< "motorNum " << motorNum << endl;
    cout << "dirNum " << dirNum << endl;
    cout<< "motor " << motor << endl;
    cout << "dir " << dir << endl;
    cout << "Num " << PwmNum << endl;
    cout << Data2 << " " << Data3 << " " << Data4 << endl;
#endif

}

void SetMotorPar::on_pB_Exit_clicked()
{
    this->close();
}
