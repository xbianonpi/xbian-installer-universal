#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mac_functions.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mac_functions fc;
     fc.mac_GetDisks();
}

MainWindow::~MainWindow()
{

    delete ui;
}

//void MainWindow::getLogicalDrives()
//{

//}
