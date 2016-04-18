/********************************************************************************
** Form generated from reading ui file 'stepmotor.ui'
**
** Created: Mon Apr 18 13:45:41 2016
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_STEPMOTOR_H
#define UI_STEPMOTOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StepMotor
{
public:
    QWidget *centralWidget;
    QPushButton *pB_Can_Set;
    QGroupBox *groupBox;
    QLabel *label;
    QLineEdit *lE_Horizon_Set;
    QMenuBar *menuBar;
    QMenu *menu_file;
    QMenu *menu_run;
    QMenu *menu_help;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *StepMotor)
    {
        if (StepMotor->objectName().isEmpty())
            StepMotor->setObjectName(QString::fromUtf8("StepMotor"));
        StepMotor->resize(1184, 584);
        centralWidget = new QWidget(StepMotor);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        pB_Can_Set = new QPushButton(centralWidget);
        pB_Can_Set->setObjectName(QString::fromUtf8("pB_Can_Set"));
        pB_Can_Set->setGeometry(QRect(70, 40, 131, 51));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(60, 210, 341, 241));
        QFont font;
        font.setPointSize(11);
        groupBox->setFont(font);
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 60, 101, 21));
        QFont font1;
        font1.setPointSize(12);
        label->setFont(font1);
        lE_Horizon_Set = new QLineEdit(groupBox);
        lE_Horizon_Set->setObjectName(QString::fromUtf8("lE_Horizon_Set"));
        lE_Horizon_Set->setGeometry(QRect(170, 60, 113, 25));
        StepMotor->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(StepMotor);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1184, 23));
        menu_file = new QMenu(menuBar);
        menu_file->setObjectName(QString::fromUtf8("menu_file"));
        menu_run = new QMenu(menuBar);
        menu_run->setObjectName(QString::fromUtf8("menu_run"));
        menu_help = new QMenu(menuBar);
        menu_help->setObjectName(QString::fromUtf8("menu_help"));
        StepMotor->setMenuBar(menuBar);
        mainToolBar = new QToolBar(StepMotor);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        StepMotor->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(StepMotor);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        StepMotor->setStatusBar(statusBar);

        menuBar->addAction(menu_file->menuAction());
        menuBar->addAction(menu_run->menuAction());
        menuBar->addAction(menu_help->menuAction());

        retranslateUi(StepMotor);

        QMetaObject::connectSlotsByName(StepMotor);
    } // setupUi

    void retranslateUi(QMainWindow *StepMotor)
    {
        StepMotor->setWindowTitle(QApplication::translate("StepMotor", "StepMotor", 0, QApplication::UnicodeUTF8));
        pB_Can_Set->setText(QApplication::translate("StepMotor", "CAN\345\217\202\346\225\260\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("StepMotor", "\347\224\265\346\234\272\345\217\202\346\225\260\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("StepMotor", "\346\260\264\345\271\263\346\227\213\350\275\254\345\221\250\346\234\237", 0, QApplication::UnicodeUTF8));
        menu_file->setTitle(QApplication::translate("StepMotor", "\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        menu_run->setTitle(QApplication::translate("StepMotor", "\350\277\220\350\241\214", 0, QApplication::UnicodeUTF8));
        menu_help->setTitle(QApplication::translate("StepMotor", "\345\270\256\345\212\251", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class StepMotor: public Ui_StepMotor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STEPMOTOR_H
