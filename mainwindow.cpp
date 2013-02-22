#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "vector"
#include "sstream"

#ifdef Q_WS_X11
#endif

#ifdef Q_WS_WIN32
#endif

#ifdef Q_OS_MAC
    #include "mac_disk.h"
    #include "mac_functions.h"
    vector<mac_disk> macDisks;
#endif

using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    refreshDrives();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshDrives()
{
    ui->cbSDCards->clear();


#ifdef Q_OS_MAC
    mac_functions mf;
    macDisks = mf.mac_GetDisks();

    for (uint i = 0; i < macDisks.size(); i++) {
        mac_disk md = macDisks[i];
        stringstream ss;
        ss << "(" << md.totalSizeInMB << " MB) " << md.mountLocation;
        ui->cbSDCards->addItem(ss.str().c_str());
    }
#endif
}

void MainWindow::restoreImage(string image, string device)
{
#ifdef Q_OS_MAC


    mac_functions mf;
    mf.restoreImage("test","test");
   // mf.restoreImage(image, device);

   // while (mf.getRestoreProgress() != -1) {
    //    ui->progressBar->setValue(mf.getRestoreProgress());
   // }
#endif
}



void MainWindow::on_btInstall_clicked()
{
    restoreImage("test","test");

}
