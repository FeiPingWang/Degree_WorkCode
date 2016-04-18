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
    void on_pB_Comfirm_clicked();
    
private slots:
    void on_pB_Cancel_clicked();

private:
    Ui::SetCANPar *ui;
};

#endif // SETCANPAR_H
