#include "dialog.h"
#include "ui_dialog.h"
#include "installer.h"


// Init of the class variable rpi_or_cubox
QString rpi_or_cubox_class::rpi_or_cubox="rpi";
rpi_or_cubox_class rpi_or_cubox_option;


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    ui->labelVersion->setText(installer_version);
}


Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_clicked()
{

    if(!ui->radioButton->isChecked())
    {
        rpi_or_cubox_option.setVal("imx6");
    }

    this->close();

    Installer installer_window;
    installer_window.show();
    installer_window.exec();
}

void Dialog::on_pushButton_2_clicked()
{
    this->close();
}

// ***
