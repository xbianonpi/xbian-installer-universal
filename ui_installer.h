/********************************************************************************
** Form generated from reading UI file 'installer.ui'
**
** Created by: Qt User Interface Compiler version 5.0.1
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
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Installer
{
public:
    QLabel *messageBar;
    QProgressBar *progressBar;
    QLabel *releaseLabel;
    QPushButton *writeButton;
    QComboBox *releaseLinks;
    QPushButton *cancelButton;
    QGraphicsView *graphicsView;
    QLabel *label;
    QComboBox *removableDevicesComboBox;

    void setupUi(QDialog *Installer)
    {
        if (Installer->objectName().isEmpty())
            Installer->setObjectName(QStringLiteral("Installer"));
        Installer->resize(307, 429);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Installer->sizePolicy().hasHeightForWidth());
        Installer->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QStringLiteral("Calibri"));
        Installer->setFont(font);
        Installer->setContextMenuPolicy(Qt::NoContextMenu);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/getrasplex.png"), QSize(), QIcon::Normal, QIcon::Off);
        Installer->setWindowIcon(icon);
#ifndef QT_NO_TOOLTIP
        Installer->setToolTip(QStringLiteral(""));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        Installer->setStatusTip(QStringLiteral(""));
#endif // QT_NO_STATUSTIP
        Installer->setLayoutDirection(Qt::LeftToRight);
        messageBar = new QLabel(Installer);
        messageBar->setObjectName(QStringLiteral("messageBar"));
        messageBar->setGeometry(QRect(10, 340, 271, 20));
        sizePolicy.setHeightForWidth(messageBar->sizePolicy().hasHeightForWidth());
        messageBar->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setFamily(QStringLiteral("Verdana"));
        font1.setPointSize(9);
        messageBar->setFont(font1);
        messageBar->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);
        progressBar = new QProgressBar(Installer);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(10, 370, 281, 21));
        progressBar->setValue(0);
        progressBar->setTextVisible(true);
        releaseLabel = new QLabel(Installer);
        releaseLabel->setObjectName(QStringLiteral("releaseLabel"));
        releaseLabel->setGeometry(QRect(10, 150, 171, 18));
        sizePolicy.setHeightForWidth(releaseLabel->sizePolicy().hasHeightForWidth());
        releaseLabel->setSizePolicy(sizePolicy);
        QFont font2;
        font2.setFamily(QStringLiteral("Verdana"));
        font2.setPointSize(10);
        font2.setBold(true);
        font2.setWeight(75);
        releaseLabel->setFont(font2);
        writeButton = new QPushButton(Installer);
        writeButton->setObjectName(QStringLiteral("writeButton"));
        writeButton->setGeometry(QRect(10, 280, 281, 31));
        QFont font3;
        font3.setPointSize(11);
        font3.setBold(true);
        font3.setWeight(75);
        writeButton->setFont(font3);
        releaseLinks = new QComboBox(Installer);
        releaseLinks->setObjectName(QStringLiteral("releaseLinks"));
        releaseLinks->setGeometry(QRect(10, 170, 281, 20));
        releaseLinks->setFont(font1);
        cancelButton = new QPushButton(Installer);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        cancelButton->setGeometry(QRect(10, 400, 281, 23));
        sizePolicy.setHeightForWidth(cancelButton->sizePolicy().hasHeightForWidth());
        cancelButton->setSizePolicy(sizePolicy);
        graphicsView = new QGraphicsView(Installer);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(9, 9, 291, 121));
        QSizePolicy sizePolicy1(QSizePolicy::Ignored, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy1);
        label = new QLabel(Installer);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 210, 231, 18));
        label->setFont(font2);
        removableDevicesComboBox = new QComboBox(Installer);
        removableDevicesComboBox->setObjectName(QStringLiteral("removableDevicesComboBox"));
        removableDevicesComboBox->setGeometry(QRect(10, 230, 281, 20));
        removableDevicesComboBox->setFont(font1);

        retranslateUi(Installer);

        QMetaObject::connectSlotsByName(Installer);
    } // setupUi

    void retranslateUi(QDialog *Installer)
    {
        Installer->setWindowTitle(QApplication::translate("Installer", "Installer", 0));
        messageBar->setText(QString());
        releaseLabel->setText(QApplication::translate("Installer", "1. Select version", 0));
        writeButton->setText(QApplication::translate("Installer", "Install", 0));
        cancelButton->setText(QApplication::translate("Installer", "Cancel", 0));
        label->setText(QApplication::translate("Installer", "2. Select SD card", 0));
    } // retranslateUi

};

namespace Ui {
    class Installer: public Ui_Installer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INSTALLER_H
