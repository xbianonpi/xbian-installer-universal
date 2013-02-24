#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "vector"
#include "sstream"
#include "iostream"
#include <QDomDocument>
#include <QNetworkAccessManager>
#include "version.h"
#include "QString"
#include <QMessageBox>
#include "stdio.h"

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
    downloadInProgress = false;
    ui->lbProgress->setAlignment(Qt::AlignHCenter);
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

    if (downloadInProgress) {
        ui->gbInstall->setEnabled(false);
        ui->gbSelectSDCard->setEnabled(false);
        ui->gbSelectVersion->setEnabled(false);
    } else {
        ui->gbInstall->setEnabled(true);
        ui->gbSelectSDCard->setEnabled(true);
        ui->gbSelectVersion->setEnabled(true);
    }
}

void MainWindow::installVersion(version ver)
{
    // Check if this version has already been downloaded
    if (!QFile::exists(QCoreApplication::applicationDirPath() + "/" + ver.getArchiveName().c_str())) {
        QString text = QString("XBian %1 has not been downloaded yet, do you want to download it now?").arg(ver.getVersionName().c_str());
        if(QMessageBox::question(this, tr("Notice"), text, QMessageBox::Yes|QMessageBox::No, QMessageBox::No) == QMessageBox::No) return;

        downloadFile(QUrl(ver.getRandomMirror().c_str()));
        this->refreshUI();
        return;
    }

    QFile * imageFile = new QFile(QCoreApplication::applicationDirPath() + "/" + ver.getArchiveName().c_str());
    if (!ver.checkMD5(imageFile)) {
        QString text = QString("Detected an invalid XBian download (MD5 does not match)");
        if(QMessageBox::question(this, tr("Notice"), text, QMessageBox::Yes|QMessageBox::No, QMessageBox::No) == QMessageBox::No) return;
    }

    cout << ver.getRandomMirror().c_str() << endl;
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

void MainWindow::downloadFile(QUrl url)
{
    filename = QFileInfo(url.path()).fileName();
    cout << filename.toStdString().c_str() << endl;
    if(QFile::exists(QCoreApplication::applicationDirPath() + "/" + filename))
        {
            if(QMessageBox::question(this, tr("Notice"),
                tr("This version has already been downloaded (%1). Redownload?").arg(filename),
                    QMessageBox::Yes|QMessageBox::No, QMessageBox::No)
                    == QMessageBox::No)
                    return;
            QFile::remove(filename);
        }

        file = new QFile(QCoreApplication::applicationDirPath() + "/" + filename);
        if(!file->open(QIODevice::WriteOnly))
            {
                QMessageBox::information(this, "Downloader",
                    tr("Unable to save the file %1: %2.")
                    .arg(filename).arg(file->errorString()));
                delete file;
                file = NULL;
                return;
            }
        downloadRequestAborted = false;
        downloadInProgress = true;
        this->refreshUI();
            reply = manager.get(QNetworkRequest(url));
            connect(reply, SIGNAL(finished()), SLOT(downloadFinished()));
            connect(reply, SIGNAL(readyRead()), this, SLOT(downloadReadyRead()));
            connect(reply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(downloadProgress(qint64,qint64)));
            //connect(progressDialog, SIGNAL(canceled()), this, SLOT(cancelDownload()));
}

void MainWindow::cancelDownload()
{
    downloadRequestAborted = true;
    reply->abort();
    //downloadButton->setEnabled(true);
}

void MainWindow::downloadFinished()
{
    downloadInProgress = false;
    file->close();
    installVersion(versions[ui->cbVersions->currentIndex()]);
}

void MainWindow::downloadReadyRead()
{
    file->write(reply->readAll());
}

void MainWindow::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    if(downloadRequestAborted)
        return;
    ui->progressBar->setMaximum(bytesTotal);
    ui->progressBar->setValue(bytesReceived);
    version ver = versions[ui->cbVersions->currentIndex()];
    double percentage = (double(bytesReceived) / bytesTotal) * 100;
    cout << percentage << endl;
    QString text = QString("Downloading XBian %1 (%2%)").arg(ver.getVersionName().c_str()).arg((int)percentage);
    ui->lbProgress->setText(text);
}

void MainWindow::on_btInstall_clicked()
{
    installVersion(versions[ui->cbVersions->currentIndex()]);
}
