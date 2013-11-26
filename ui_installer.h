/********************************************************************************
** Form generated from reading UI file 'installer.ui'
**
** Created: Wed Mar 27 12:43:43 2013
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INSTALLER_H
#define UI_INSTALLER_H

#include <QtCore/QVariant>
#include <QtWidgets>

QT_BEGIN_NAMESPACE

class Ui_Installer
{
public:
    QLabel *lbSelectVersion;
    QPushButton *btInstall;
    QComboBox *cbVersion;
    QLabel *lbSelectSD;
    QComboBox *cbSDcards;
    QPushButton *btAbout;

    void setupUi(QDialog *Installer)
    {
        if (Installer->objectName().isEmpty())
            Installer->setObjectName(QString::fromUtf8("Installer"));
        Installer->resize(307, 179);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Installer->sizePolicy().hasHeightForWidth());
        Installer->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("Calibri"));
        Installer->setFont(font);
        Installer->setContextMenuPolicy(Qt::NoContextMenu);
        QIcon icon;
        icon.addFile(QString::fromUtf8("icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        Installer->setWindowIcon(icon);
#ifndef QT_NO_TOOLTIP
        Installer->setToolTip(QString::fromUtf8(""));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        Installer->setStatusTip(QString::fromUtf8(""));
#endif // QT_NO_STATUSTIP
        Installer->setLayoutDirection(Qt::LeftToRight);
        Installer->setSizeGripEnabled(false);
        Installer->setModal(false);
        lbSelectVersion = new QLabel(Installer);
        lbSelectVersion->setObjectName(QString::fromUtf8("lbSelectVersion"));
        lbSelectVersion->setGeometry(QRect(10, 10, 171, 18));
        sizePolicy.setHeightForWidth(lbSelectVersion->sizePolicy().hasHeightForWidth());
        lbSelectVersion->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setFamily(QString::fromUtf8("Verdana"));
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        lbSelectVersion->setFont(font1);
        btInstall = new QPushButton(Installer);
        btInstall->setObjectName(QString::fromUtf8("btInstall"));
        btInstall->setGeometry(QRect(10, 140, 281, 31));
        QFont font2;
        font2.setPointSize(11);
        font2.setBold(true);
        font2.setWeight(75);
        btInstall->setFont(font2);
        cbVersion = new QComboBox(Installer);
        cbVersion->setObjectName(QString::fromUtf8("cbVersion"));
        cbVersion->setGeometry(QRect(10, 30, 281, 20));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Verdana"));
        font3.setPointSize(9);
        cbVersion->setFont(font3);
        lbSelectSD = new QLabel(Installer);
        lbSelectSD->setObjectName(QString::fromUtf8("lbSelectSD"));
        lbSelectSD->setGeometry(QRect(10, 70, 231, 18));
        lbSelectSD->setFont(font1);
        cbSDcards = new QComboBox(Installer);
        cbSDcards->setObjectName(QString::fromUtf8("cbSDcards"));
        cbSDcards->setGeometry(QRect(10, 90, 281, 20));
        cbSDcards->setFont(font3);
        btAbout = new QPushButton(Installer);
        btAbout->setObjectName(QString::fromUtf8("btAbout"));
        btAbout->setGeometry(QRect(250, 0, 75, 21));
        QFont font4;
        font4.setUnderline(true);
        btAbout->setFont(font4);
        btAbout->setFlat(true);

        retranslateUi(Installer);

        QMetaObject::connectSlotsByName(Installer);
    } // setupUi

    void retranslateUi(QDialog *Installer)
    {
        Installer->setWindowTitle(QApplication::translate("Installer", "XBian installer", 0, 0));
        lbSelectVersion->setText(QApplication::translate("Installer", "1. Select version", 0, 0));
        btInstall->setText(QApplication::translate("Installer", "Install", 0, 0));
        lbSelectSD->setText(QApplication::translate("Installer", "2. Select SD card", 0, 0));
        btAbout->setText(QApplication::translate("Installer", "About", 0, 0));
    } // retranslateUi

};

namespace Ui {
    class Installer: public Ui_Installer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INSTALLER_H
