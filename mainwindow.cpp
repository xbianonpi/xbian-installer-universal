#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "vector"
#include "sstream"
#include "iostream"
#include <QtXml/QXmlSimpleReader>
#include <QNetworkAccessManager>
#include "version.h"

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

#define mirrorsXMLLocation "http://download.brantje.com/xbian/mirrors.xml"

QBuffer xmldata;
int XMLRequestId;
vector<version> versions;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initXMLRequestFromWeb(QUrl(mirrorsXMLLocation));
    refreshDrives();
}

void MainWindow::initXMLRequestFromWeb(QUrl url)
{
    QNetworkAccessManager * manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(fileIsReady(QNetworkReply*)) );
    manager->get(QNetworkRequest(url));
}

void MainWindow::fileIsReady( QNetworkReply * reply)
{
    QXmlStreamReader reader(reply);

    while (!reader.atEnd() && !reader.hasError()) {
        QXmlStreamReader::TokenType token = reader.readNext();
        if(token == QXmlStreamReader::StartDocument)  continue;
        if(token == QXmlStreamReader::StartElement) {
            if (reader.name() == "mirrors") continue;
            if (reader.name() == "version") versions.push_back(version(reader));
        }
    }

    reader.clear();

    this->refreshUI();
}

void MainWindow::refreshUI() {
    ui->cbVersions->clear();
    for (version v : versions) {
        ui->cbVersions->addItem(v.getVersionName());
    }
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
