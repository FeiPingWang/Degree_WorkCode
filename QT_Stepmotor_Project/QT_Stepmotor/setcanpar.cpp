#include "setcanpar.h"
#include "ui_setcanpar.h"

SetCANPar::SetCANPar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetCANPar)
{
    ui->setupUi(this);
}

SetCANPar::~SetCANPar()
{
    delete ui;
}

/* 配置参数确认对话框 */
void SetCANPar::on_pB_Comfirm_clicked()
{
    QMessageBox::warning(this,("warning"),QString("确定配置CAN参数？"),QMessageBox::Yes,QMessageBox::No);
}

void SetCANPar::on_pB_Cancel_clicked()
{
    this->close();
}
