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
    QString getcB_Can(){
        if(m_strCan != "")
            return m_strCan;
        else
            return "can0";
    }
    
private slots:
    void on_pB_Cancel_clicked();
    void on_pB_Comfirm_clicked();

signals:
    void stateChanged();
    void displySignal(QString router,QString mode,QString bitrate);

private:
    Ui::SetCANPar *ui;
    QString m_strCan;
    QString m_strMode;
    QString m_strBit;
};

#endif // SETCANPAR_H
