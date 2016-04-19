#include "setcanpar.h"
#include "ui_setcanpar.h"

SetCANPar::SetCANPar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetCANPar)
{
    ui->setupUi(this);
    m_strCan = "can0";      //初始默认值
    m_strMode= "普通模式";
    m_strBit = "500000";
}

SetCANPar::~SetCANPar()
{
    delete ui;
}

/* 配置参数取消对话框 */
void SetCANPar::on_pB_Cancel_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm", "Do you want to save and exit?", QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)       //确认退出
    {
        this->close();
    }
}

/* 配置参数确认对话框 */
void SetCANPar::on_pB_Comfirm_clicked()
{
    QMessageBox::StandardButton confirm;
    confirm = QMessageBox::question(this, "Confirm", "Do you want to save and exit?", QMessageBox::Yes | QMessageBox::No);

    if(confirm == QMessageBox::Yes)             //确认退出
    {
        m_strCan = ui->cB_Can->currentText();   //获取参数
        m_strMode = ui->cB_Mode->currentText();
        m_strBit = ui->lE_Bitrate->text();

        QStringList list;  //开启can0
        list << "can0" << "stop";
        QProcess *process1 = new QProcess(this);
        process1 -> execute("canconfig",list);   //1.配置第一步

        list.clear();
        list << "can0" << "bitrate" << m_strBit << "ctrlmode" << "triple-sampling" \
             << "on" << "listen-only" << "off" << "loopback" << "off";

        QProcess *process2 = new QProcess(this);
        process2-> execute("canconfig",list);

        list.clear();
        list << "can0" << "start";
        QProcess *process3 = new QProcess(this);
        process3-> execute("canconfig",list);  //完成配置

        emit stateChanged();                 //发送状态改变参数
        this->close();
    }

}
