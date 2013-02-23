#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "vector"
#include "sstream"
#include "iostream"
#include <QDomDocument>
#include <QNetworkAccessManager>
#include "version.h"
#include "QString"

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

void MainWindow::fileIsReady(QNetworkReply* reply)
{
    versions.clear();
    QDomDocument xml;
    xml.setContent(reply);

    QDomElement docElem = xml.documentElement();
    QString rootTag = docElem.tagName(); // == persons
    QDomNodeList nodeList = docElem.elementsByTagName("version");

    for (int i = 0; i < nodeList.count(); i++) {
        QDomElement el = nodeList.at(i).toElement();

        QDomNode pEntries = el.firstChild();
        string name;
        string locations;
        string md5;

        while(!pEntries.isNull()) {
            QDomElement peData = pEntries.toElement();
            QString tagNam = peData.tagName();

            if (tagNam == "name") name = peData.text().toStdString();
            if (tagNam == "locations") locations = peData.text().toStdString();
            if (tagNam == "md5") md5 = peData.text().toStdString();

            pEntries = pEntries.nextSibling();
        }

        version v(name, locations, md5);
        versions.push_back(v);
    }

    this->refreshUI();
}

void MainWindow::refreshUI() {
    ui->cbVersions->clear();


    for (version v : versions) {
        ui->cbVersions->addItem(v.getVersionName().c_str());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshDrives()
{
    ui->cbVolumes->clear();

#ifdef Q_OS_MAC
    mac_functions mf;
    macDisks = mf.mac_GetDisks();

    for (uint i = 0; i < macDisks.size(); i++) {
        mac_disk md = macDisks[i];
        stringstream ss;

        ss << "(" << md.getTotalSizeInMB() << " MB) " << md.getMountLocation();
        ui->cbVolumes->addItem(ss.str().c_str());
    }
#endif
}

void MainWindow::restoreImage(string image)
{
#ifdef Q_OS_MAC
    mac_disk md = macDisks[ui->cbVolumes->currentIndex()];
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
