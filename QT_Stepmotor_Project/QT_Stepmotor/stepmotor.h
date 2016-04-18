#ifndef STEPMOTOR_H
#define STEPMOTOR_H

#include <QMainWindow>
#include "setcanpar.h"

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

private:
    Ui::StepMotor *ui;
    SetCANPar *setcanpar;       //can的设置对话框对象
};

#endif // STEPMOTOR_H
