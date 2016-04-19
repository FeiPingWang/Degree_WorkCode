/********************************************************************************
** Form generated from reading ui file 'stepmotor.ui'
**
** Created: Tue Apr 19 11:06:38 2016
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
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StepMotor
{
public:
    QAction *action;
    QAction *action_2;
    QAction *action_3;
    QAction *action_4;
    QAction *action_Exit;
    QWidget *centralWidget;
    QPushButton *pB_Can_Set;
    QGroupBox *groupBox;
    QLabel *label;
    QLineEdit *lE_Horizon_Set;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *lb_Horizon_Heigh;
    QLabel *lb_Vertical_Heigh;
    QLabel *lb_Distance;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *lE_Horizon_Heigh;
    QLineEdit *lE_Horizon_Heigh_2;
    QLineEdit *lE_Distance;
    QLabel *lb_Time;
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
        StepMotor->resize(822, 505);
        action = new QAction(StepMotor);
        action->setObjectName(QString::fromUtf8("action"));
        action_2 = new QAction(StepMotor);
        action_2->setObjectName(QString::fromUtf8("action_2"));
        action_3 = new QAction(StepMotor);
        action_3->setObjectName(QString::fromUtf8("action_3"));
        action_4 = new QAction(StepMotor);
        action_4->setObjectName(QString::fromUtf8("action_4"));
        action_Exit = new QAction(StepMotor);
        action_Exit->setObjectName(QString::fromUtf8("action_Exit"));
        centralWidget = new QWidget(StepMotor);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        pB_Can_Set = new QPushButton(centralWidget);
        pB_Can_Set->setObjectName(QString::fromUtf8("pB_Can_Set"));
        pB_Can_Set->setGeometry(QRect(60, 90, 101, 31));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(60, 190, 341, 241));
        QFont font;
        font.setPointSize(12);
        groupBox->setFont(font);
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 40, 101, 21));
        label->setFont(font);
        lE_Horizon_Set = new QLineEdit(groupBox);
        lE_Horizon_Set->setObjectName(QString::fromUtf8("lE_Horizon_Set"));
        lE_Horizon_Set->setGeometry(QRect(170, 40, 113, 25));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(450, 120, 341, 321));
        groupBox_2->setFont(font);
        layoutWidget = new QWidget(groupBox_2);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(40, 70, 73, 231));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setMargin(11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lb_Horizon_Heigh = new QLabel(layoutWidget);
        lb_Horizon_Heigh->setObjectName(QString::fromUtf8("lb_Horizon_Heigh"));

        verticalLayout->addWidget(lb_Horizon_Heigh);

        lb_Vertical_Heigh = new QLabel(layoutWidget);
        lb_Vertical_Heigh->setObjectName(QString::fromUtf8("lb_Vertical_Heigh"));

        verticalLayout->addWidget(lb_Vertical_Heigh);

        lb_Distance = new QLabel(layoutWidget);
        lb_Distance->setObjectName(QString::fromUtf8("lb_Distance"));

        verticalLayout->addWidget(lb_Distance);

        layoutWidget1 = new QWidget(groupBox_2);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(200, 70, 111, 231));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setMargin(11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        lE_Horizon_Heigh = new QLineEdit(layoutWidget1);
        lE_Horizon_Heigh->setObjectName(QString::fromUtf8("lE_Horizon_Heigh"));

        verticalLayout_2->addWidget(lE_Horizon_Heigh);

        lE_Horizon_Heigh_2 = new QLineEdit(layoutWidget1);
        lE_Horizon_Heigh_2->setObjectName(QString::fromUtf8("lE_Horizon_Heigh_2"));

        verticalLayout_2->addWidget(lE_Horizon_Heigh_2);

        lE_Distance = new QLineEdit(layoutWidget1);
        lE_Distance->setObjectName(QString::fromUtf8("lE_Distance"));

        verticalLayout_2->addWidget(lE_Distance);

        lb_Time = new QLabel(centralWidget);
        lb_Time->setObjectName(QString::fromUtf8("lb_Time"));
        lb_Time->setGeometry(QRect(640, 0, 181, 17));
        StepMotor->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(StepMotor);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 822, 26));
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
        menu_file->addAction(action);
        menu_file->addAction(action_2);
        menu_run->addAction(action_3);
        menu_run->addAction(action_4);
        menu_run->addAction(action_Exit);

        retranslateUi(StepMotor);

        QMetaObject::connectSlotsByName(StepMotor);
    } // setupUi

    void retranslateUi(QMainWindow *StepMotor)
    {
        StepMotor->setWindowTitle(QApplication::translate("StepMotor", "StepMotor", 0, QApplication::UnicodeUTF8));
        action->setText(QApplication::translate("StepMotor", "\344\277\235\345\255\230\351\205\215\347\275\256\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        action_2->setText(QApplication::translate("StepMotor", "\345\257\274\345\205\245\351\205\215\347\275\256\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        action_3->setText(QApplication::translate("StepMotor", "\345\274\200\345\247\213", 0, QApplication::UnicodeUTF8));
        action_4->setText(QApplication::translate("StepMotor", "\345\201\234\346\255\242", 0, QApplication::UnicodeUTF8));
        action_Exit->setText(QApplication::translate("StepMotor", "\351\200\200\345\207\272", 0, QApplication::UnicodeUTF8));
        pB_Can_Set->setText(QApplication::translate("StepMotor", "CAN\345\217\202\346\225\260\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("StepMotor", "\347\224\265\346\234\272\345\217\202\346\225\260\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("StepMotor", "\346\260\264\345\271\263\346\227\213\350\275\254\345\221\250\346\234\237", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("StepMotor", "\345\256\236\346\227\266\346\230\276\347\244\272\345\214\272", 0, QApplication::UnicodeUTF8));
        lb_Horizon_Heigh->setText(QApplication::translate("StepMotor", "\346\260\264\345\271\263\351\253\230\345\272\246", 0, QApplication::UnicodeUTF8));
        lb_Vertical_Heigh->setText(QApplication::translate("StepMotor", " \345\236\202\347\233\264\351\253\230\345\272\246", 0, QApplication::UnicodeUTF8));
        lb_Distance->setText(QApplication::translate("StepMotor", "  \350\267\235     \347\246\273", 0, QApplication::UnicodeUTF8));
        lb_Time->setText(QApplication::translate("StepMotor", "Time", 0, QApplication::UnicodeUTF8));
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
