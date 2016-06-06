#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QProcess>
#include <QStringList>
#include <QString>
#include <QTime>
#include <QDateTime>
#include <QRegExp>
#include <QThread>
#include <QMessageBox>
#include "Threadrec.h"
#include "Threadrec1.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void timeupdate();

    void on_actQuit_triggered();

    void on_actRun_triggered();

    void on_actStop_triggered();

    void on_pBSend_clicked();

private:
    Ui::MainWindow *ui;

    QTimer *DateTime;       //时间显示
    QTimer *time;
    ThreadRec *m_threadRecv0;
    ThreadRec1 *m_threadRecv1;
    QString m_strCan;
    QString m_strBit;
   // QString m_strDisplay1;  //显示接收的消息Can1
   // QString m_strDisplay2; //显示接收的消息Can2
    char *m_cptr0[10];     //接收用的参数存储
    char *m_cptr1[10];     //接收用的参数存储
};

#endif // MAINWINDOW_H
