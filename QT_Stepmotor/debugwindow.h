#ifndef DEBUGWINDOW_H
#define DEBUGWINDOW_H

#include <QDialog>
#include "Threadrec.h"
#include "setcanpar.h"
#include "Headed.h"
namespace Ui {
class DebugWindow;
}

class DebugWindow : public QDialog
{
    Q_OBJECT
public:
    explicit DebugWindow(QWidget *parent = 0);
    ~DebugWindow();
    
private slots:
    void on_D_pB_Exit_clicked();
    void cbStateChanged();      //can设置改变，重新设置
    void setDisLabel(QString,QString,QString);
    void ShowCanMsg(QString str);

private:
    Ui::DebugWindow *ui;
    char *m_cptr[10];
    ThreadRec *m_threadRecv0;
    QString m_strDisplay;
};

#endif // DEBUGWINDOW_H
