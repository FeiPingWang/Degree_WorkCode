#ifndef STEPMOTOR_H
#define STEPMOTOR_H

#include <QMainWindow>
#include "setcanpar.h"
#include "debugwindow.h"
#include "setmotorpar.h"
#include "Threadrec.h"
namespace Ui {
class StepMotor;
}

class StepMotor : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit StepMotor(QWidget *parent = 0);
    ~StepMotor();
    
private slots:
    void on_pB_Can_Set_clicked();

    void on_action_Exit_triggered();
    void timeupdate();
    void on_action_Stop_triggered();
    void on_pushButton_clicked();
    void on_pB_motor_set_clicked();
    void on_pB_Start_Debug_clicked();
    void getMotorPar(QStringList);      //得到CAN的参数，准备发送

private:
    Ui::StepMotor *ui;
    SetCANPar *setcanpar;       //can的设置对话框对象
    DebugWindow *debugwindow;
    SetMotorPar *setMotorPar;
    QTimer *DateTime;        //实时时间显示函数
    QStringList SendList;   //调试用发送的消息
  //  char *m_cptr[10];
    ThreadRec *m_threadRecv0;
};

#endif // STEPMOTOR_H
