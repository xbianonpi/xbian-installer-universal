// ***

#include "dialog.h"
#include "ui_dialog.h"
#include "installer.h"
#include <QUrl>
#include <iostream>

QUrl sourceForgeRSS(sourceForgeRSS_release);
//sourceForgeRSSUrl=sourceForgeRSS_release;
QUrl sourceForgeURL::sourceForgeURLtype = sourceForgeRSS;

sourceForgeURL sourceForgeOption;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);


}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_clicked()
{

    if(!ui->radioButton->isChecked())
    {
        sourceForgeRSS=sourceForgeRSS_testing;
        sourceForgeOption.setVal(sourceForgeRSS);
    }

    this->close();

    Installer w;
    //w.setWindowTitle("XBian installer (version 1.1)");
    w.show();
    w.exec();
}

void Dialog::on_pushButton_2_clicked()
{
    this->close();
}

// ***
