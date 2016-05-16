#ifndef SETMOTORPAR_H
#define SETMOTORPAR_H

#include <QDialog>
#include "Headed.h"

namespace Ui {
class SetMotorPar;
}

class SetMotorPar : public QDialog
{
    Q_OBJECT
    
public:
    explicit SetMotorPar(QWidget *parent = 0);
    ~SetMotorPar();
    
private slots:
    void on_pB_Eixt_clicked();

    void on_pB_Confirm_clicked();

signals:
    void SendMotorPar(QStringList vMoPar);

private:
    Ui::SetMotorPar *ui;
    QStringList vMoPar;  //保存所有的参数，当成信号参数发送出去
};

#endif // SETMOTORPAR_H
