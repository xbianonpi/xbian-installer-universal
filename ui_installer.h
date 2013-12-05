/********************************************************************************
** Form generated from reading UI file 'installer.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INSTALLER_H
#define UI_INSTALLER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Installer
{
public:
    QLabel *lbSelectVersion;
    QPushButton *btInstall;
    QComboBox *cbVersion;
    QLabel *lbSelectSD;
    QComboBox *cbSDcards;
    QLabel *labelVersion;

    void setupUi(QDialog *Installer)
    {
        if (Installer->objectName().isEmpty())
            Installer->setObjectName(QStringLiteral("Installer"));
        Installer->resize(307, 182);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Installer->sizePolicy().hasHeightForWidth());
        Installer->setSizePolicy(sizePolicy);
        Installer->setMinimumSize(QSize(307, 182));
        Installer->setMaximumSize(QSize(307, 182));
        QFont font;
        font.setFamily(QStringLiteral("Calibri"));
        Installer->setFont(font);
        Installer->setContextMenuPolicy(Qt::NoContextMenu);
        QIcon icon;
        icon.addFile(QStringLiteral("icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        Installer->setWindowIcon(icon);
#ifndef QT_NO_TOOLTIP
        Installer->setToolTip(QStringLiteral(""));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        Installer->setStatusTip(QStringLiteral(""));
#endif // QT_NO_STATUSTIP
        Installer->setLayoutDirection(Qt::LeftToRight);
        Installer->setSizeGripEnabled(false);
        Installer->setModal(false);
        lbSelectVersion = new QLabel(Installer);
        lbSelectVersion->setObjectName(QStringLiteral("lbSelectVersion"));
        lbSelectVersion->setGeometry(QRect(10, 10, 171, 18));
        sizePolicy.setHeightForWidth(lbSelectVersion->sizePolicy().hasHeightForWidth());
        lbSelectVersion->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setFamily(QStringLiteral("Verdana"));
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        lbSelectVersion->setFont(font1);
        btInstall = new QPushButton(Installer);
        btInstall->setObjectName(QStringLiteral("btInstall"));
        btInstall->setGeometry(QRect(10, 140, 281, 31));
        QFont font2;
        font2.setPointSize(11);
        font2.setBold(true);
        font2.setWeight(75);
        btInstall->setFont(font2);
        cbVersion = new QComboBox(Installer);
        cbVersion->setObjectName(QStringLiteral("cbVersion"));
        cbVersion->setGeometry(QRect(10, 30, 281, 20));
        QFont font3;
        font3.setFamily(QStringLiteral("Verdana"));
        font3.setPointSize(9);
        cbVersion->setFont(font3);
        lbSelectSD = new QLabel(Installer);
        lbSelectSD->setObjectName(QStringLiteral("lbSelectSD"));
        lbSelectSD->setGeometry(QRect(10, 70, 231, 18));
        lbSelectSD->setFont(font1);
        cbSDcards = new QComboBox(Installer);
        cbSDcards->setObjectName(QStringLiteral("cbSDcards"));
        cbSDcards->setGeometry(QRect(10, 90, 281, 20));
        cbSDcards->setFont(font3);
        labelVersion = new QLabel(Installer);
        labelVersion->setObjectName(QStringLiteral("labelVersion"));
        labelVersion->setGeometry(QRect(220, 0, 81, 19));
        QFont font4;
        font4.setFamily(QStringLiteral("Geeza Pro"));
        font4.setPointSize(10);
        labelVersion->setFont(font4);

        retranslateUi(Installer);

        QMetaObject::connectSlotsByName(Installer);
    } // setupUi

    void retranslateUi(QDialog *Installer)
    {
        Installer->setWindowTitle(QApplication::translate("Installer", "XBian installer", 0));
        lbSelectVersion->setText(QApplication::translate("Installer", "1. Select version", 0));
        btInstall->setText(QApplication::translate("Installer", "Install", 0));
        lbSelectSD->setText(QApplication::translate("Installer", "2. Select SD card", 0));
        labelVersion->setText(QApplication::translate("Installer", "Version 1.0", 0));
    } // retranslateUi

};

namespace Ui {
    class Installer: public Ui_Installer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INSTALLER_H
