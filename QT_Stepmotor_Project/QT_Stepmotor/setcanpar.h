#ifndef SETCANPAR_H
#define SETCANPAR_H

#include <QDialog>
#include "Headed.h"

namespace Ui {
class SetCANPar;
}

class SetCANPar : public QDialog
{
    Q_OBJECT
    
public:
    explicit SetCANPar(QWidget *parent = 0);
    ~SetCANPar();
    
private slots:
    void on_pB_Cancel_clicked();

    void on_pB_Comfirm_clicked();

signals:
    void stateChanged();

private:
    Ui::SetCANPar *ui;
    QString m_strCan;
    QString m_strMode;
    QString m_strBit;
};

#endif // SETCANPAR_H
