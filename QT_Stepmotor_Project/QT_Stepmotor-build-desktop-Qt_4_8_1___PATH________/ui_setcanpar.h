/********************************************************************************
** Form generated from reading UI file 'setcanpar.ui'
**
** Created: Mon Apr 18 16:02:36 2016
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
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
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SetCANPar
{
public:
    QGroupBox *gB_SetPar;
    QLabel *l_Can;
    QComboBox *cB_Can;
    QLabel *l_Bit;
    QLineEdit *lE_Bitrate;
    QPushButton *pB_Comfirm;
    QPushButton *pB_Cancel;
    QLabel *lb_Mode;
    QComboBox *cB_Mode;

    void setupUi(QDialog *SetCANPar)
    {
        if (SetCANPar->objectName().isEmpty())
            SetCANPar->setObjectName(QString::fromUtf8("SetCANPar"));
        SetCANPar->resize(386, 285);
        gB_SetPar = new QGroupBox(SetCANPar);
        gB_SetPar->setObjectName(QString::fromUtf8("gB_SetPar"));
        gB_SetPar->setEnabled(true);
        gB_SetPar->setGeometry(QRect(60, 40, 221, 171));
        l_Can = new QLabel(gB_SetPar);
        l_Can->setObjectName(QString::fromUtf8("l_Can"));
        l_Can->setGeometry(QRect(10, 20, 58, 15));
        cB_Can = new QComboBox(gB_SetPar);
        cB_Can->setObjectName(QString::fromUtf8("cB_Can"));
        cB_Can->setGeometry(QRect(90, 10, 82, 25));
        l_Bit = new QLabel(gB_SetPar);
        l_Bit->setObjectName(QString::fromUtf8("l_Bit"));
        l_Bit->setGeometry(QRect(10, 90, 58, 15));
        lE_Bitrate = new QLineEdit(gB_SetPar);
        lE_Bitrate->setObjectName(QString::fromUtf8("lE_Bitrate"));
        lE_Bitrate->setEnabled(true);
        lE_Bitrate->setGeometry(QRect(90, 85, 81, 20));
        pB_Comfirm = new QPushButton(gB_SetPar);
        pB_Comfirm->setObjectName(QString::fromUtf8("pB_Comfirm"));
        pB_Comfirm->setGeometry(QRect(10, 120, 80, 26));
        pB_Cancel = new QPushButton(gB_SetPar);
        pB_Cancel->setObjectName(QString::fromUtf8("pB_Cancel"));
        pB_Cancel->setGeometry(QRect(100, 120, 80, 26));
        lb_Mode = new QLabel(gB_SetPar);
        lb_Mode->setObjectName(QString::fromUtf8("lb_Mode"));
        lb_Mode->setGeometry(QRect(20, 60, 58, 15));
        cB_Mode = new QComboBox(gB_SetPar);
        cB_Mode->setObjectName(QString::fromUtf8("cB_Mode"));
        cB_Mode->setGeometry(QRect(90, 50, 82, 25));

        retranslateUi(SetCANPar);

        QMetaObject::connectSlotsByName(SetCANPar);
    } // setupUi

    void retranslateUi(QDialog *SetCANPar)
    {
        SetCANPar->setWindowTitle(QApplication::translate("SetCANPar", "Dialog", 0, QApplication::UnicodeUTF8));
        gB_SetPar->setTitle(QApplication::translate("SetCANPar", "SetPar", 0, QApplication::UnicodeUTF8));
        l_Can->setText(QApplication::translate("SetCANPar", "CAN\351\200\211\346\213\251", 0, QApplication::UnicodeUTF8));
        cB_Can->clear();
        cB_Can->insertItems(0, QStringList()
         << QApplication::translate("SetCANPar", "can0", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetCANPar", "can1", 0, QApplication::UnicodeUTF8)
        );
        l_Bit->setText(QApplication::translate("SetCANPar", "\344\275\215\351\200\237\347\216\207", 0, QApplication::UnicodeUTF8));
        lE_Bitrate->setText(QApplication::translate("SetCANPar", "500000", 0, QApplication::UnicodeUTF8));
        pB_Comfirm->setText(QApplication::translate("SetCANPar", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        pB_Cancel->setText(QApplication::translate("SetCANPar", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
        lb_Mode->setText(QApplication::translate("SetCANPar", "\346\250\241\345\274\217", 0, QApplication::UnicodeUTF8));
        cB_Mode->clear();
        cB_Mode->insertItems(0, QStringList()
         << QApplication::translate("SetCANPar", "\346\231\256\351\200\232\346\250\241\345\274\217", 0, QApplication::UnicodeUTF8)
        );
    } // retranslateUi

};

namespace Ui {
    class SetCANPar: public Ui_SetCANPar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETCANPAR_H
