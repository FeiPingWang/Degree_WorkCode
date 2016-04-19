/********************************************************************************
** Form generated from reading ui file 'setcanpar.ui'
**
** Created: Tue Apr 19 11:06:38 2016
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_SETCANPAR_H
#define UI_SETCANPAR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SetCANPar
{
public:
    QGroupBox *gB_SetPar;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QComboBox *cB_Can;
    QComboBox *cB_Mode;
    QLineEdit *lE_Bitrate;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QLabel *l_Can;
    QLabel *lb_Mode;
    QLabel *l_Bit;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pB_Comfirm;
    QPushButton *pB_Cancel;
    QLabel *label;
    QLabel *lb_test;

    void setupUi(QDialog *SetCANPar)
    {
        if (SetCANPar->objectName().isEmpty())
            SetCANPar->setObjectName(QString::fromUtf8("SetCANPar"));
        SetCANPar->resize(386, 285);
        gB_SetPar = new QGroupBox(SetCANPar);
        gB_SetPar->setObjectName(QString::fromUtf8("gB_SetPar"));
        gB_SetPar->setEnabled(true);
        gB_SetPar->setGeometry(QRect(60, 40, 221, 171));
        layoutWidget = new QWidget(gB_SetPar);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(90, 10, 131, 101));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        cB_Can = new QComboBox(layoutWidget);
        cB_Can->setObjectName(QString::fromUtf8("cB_Can"));

        verticalLayout_2->addWidget(cB_Can);

        cB_Mode = new QComboBox(layoutWidget);
        cB_Mode->setObjectName(QString::fromUtf8("cB_Mode"));

        verticalLayout_2->addWidget(cB_Mode);

        lE_Bitrate = new QLineEdit(layoutWidget);
        lE_Bitrate->setObjectName(QString::fromUtf8("lE_Bitrate"));
        lE_Bitrate->setEnabled(true);

        verticalLayout_2->addWidget(lE_Bitrate);

        layoutWidget1 = new QWidget(gB_SetPar);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(11, 8, 62, 101));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        l_Can = new QLabel(layoutWidget1);
        l_Can->setObjectName(QString::fromUtf8("l_Can"));

        verticalLayout->addWidget(l_Can);

        lb_Mode = new QLabel(layoutWidget1);
        lb_Mode->setObjectName(QString::fromUtf8("lb_Mode"));

        verticalLayout->addWidget(lb_Mode);

        l_Bit = new QLabel(layoutWidget1);
        l_Bit->setObjectName(QString::fromUtf8("l_Bit"));

        verticalLayout->addWidget(l_Bit);

        layoutWidget2 = new QWidget(gB_SetPar);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(11, 131, 211, 30));
        horizontalLayout = new QHBoxLayout(layoutWidget2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pB_Comfirm = new QPushButton(layoutWidget2);
        pB_Comfirm->setObjectName(QString::fromUtf8("pB_Comfirm"));

        horizontalLayout->addWidget(pB_Comfirm);

        pB_Cancel = new QPushButton(layoutWidget2);
        pB_Cancel->setObjectName(QString::fromUtf8("pB_Cancel"));

        horizontalLayout->addWidget(pB_Cancel);

        label = new QLabel(SetCANPar);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(70, 20, 131, 17));
        lb_test = new QLabel(SetCANPar);
        lb_test->setObjectName(QString::fromUtf8("lb_test"));
        lb_test->setGeometry(QRect(270, 230, 66, 17));

        retranslateUi(SetCANPar);

        QMetaObject::connectSlotsByName(SetCANPar);
    } // setupUi

    void retranslateUi(QDialog *SetCANPar)
    {
        SetCANPar->setWindowTitle(QApplication::translate("SetCANPar", "Dialog", 0, QApplication::UnicodeUTF8));
        gB_SetPar->setTitle(QString());
        cB_Can->clear();
        cB_Can->insertItems(0, QStringList()
         << QApplication::translate("SetCANPar", "can0", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetCANPar", "can1", 0, QApplication::UnicodeUTF8)
        );
        cB_Mode->clear();
        cB_Mode->insertItems(0, QStringList()
         << QApplication::translate("SetCANPar", "\346\231\256\351\200\232\346\250\241\345\274\217", 0, QApplication::UnicodeUTF8)
        );
        lE_Bitrate->setText(QApplication::translate("SetCANPar", "500000", 0, QApplication::UnicodeUTF8));
        l_Can->setText(QApplication::translate("SetCANPar", "CAN\351\200\211\346\213\251", 0, QApplication::UnicodeUTF8));
        lb_Mode->setText(QApplication::translate("SetCANPar", "\346\250\241\345\274\217", 0, QApplication::UnicodeUTF8));
        l_Bit->setText(QApplication::translate("SetCANPar", "\344\275\215\351\200\237\347\216\207", 0, QApplication::UnicodeUTF8));
        pB_Comfirm->setText(QApplication::translate("SetCANPar", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        pB_Cancel->setText(QApplication::translate("SetCANPar", "\351\200\200\345\207\272", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SetCANPar", "\350\256\276\347\275\256CAN\346\200\273\347\272\277\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        lb_test->setText(QApplication::translate("SetCANPar", "TextLabel", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(SetCANPar);
    } // retranslateUi

};

namespace Ui {
    class SetCANPar: public Ui_SetCANPar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETCANPAR_H
