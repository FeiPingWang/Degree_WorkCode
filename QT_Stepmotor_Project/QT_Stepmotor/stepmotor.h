#ifndef STEPMOTOR_H
#define STEPMOTOR_H

#include <QMainWindow>
#include "setcanpar.h"
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
    void cbStateChanged();

private:
    Ui::StepMotor *ui;
    SetCANPar *setcanpar;       //can的设置对话框对象
    QTimer *DateTime;        //实时时间显示函数
    char *m_cptr[10];
    ThreadRec *m_threadRecv0;
};

#endif // STEPMOTOR_H
