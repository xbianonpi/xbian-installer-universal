#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "vector"
#include "sstream"
#include "iostream"

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

void MainWindow::restoreImage(string image)
{
#ifdef Q_OS_MAC
    mac_disk md = macDisks[ui->cbSDCards->currentIndex()];
    md.getDiskNumber();

    std::cout << "restore"  << std::endl;
    ui->progressBar->setValue(0);
    mac_functions mf;
    mf.restoreImage(image,md);

    while (mf.getRestoreProgress() != -1) {
        cout << mf.getRestoreProgress();
        ui->progressBar->setValue(mf.getRestoreProgress());
    }



#endif
}



void MainWindow::on_btInstall_clicked()
{
    restoreImage("/Users/Koenkk/Desktop/i.img");
}
