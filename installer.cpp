#include "installer.h"
#include "ui_installer.h"

#include <QString>
#include <QFile>
#include <QFileDialog>
#include <iostream>
#include <QUrl>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QMessageBox>

#if defined(Q_OS_WIN)
#include "diskwriter_windows.h"
#elif defined(Q_OS_UNIX)
#include "diskwriter_unix.h"
#endif

// TODO: Get chunk size from server, or whatever
#define CHUNKSIZE 1*1024*1024
#define installerVersion 0.1

// Mirror information
#define sourceForgeRSS "http://sourceforge.net/api/file/index/project-id/1428221/atom"
#define md5file "https://downloads.sourceforge.net/project/xbian/release/MD5.txt?r=&ts=1364648856&use_mirror=switch"

Installer::Installer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Installer),
    state(STATE_IDLE),
    bytesDownloaded(0)
{
    ui->setupUi(this);
    manager.setParent(this);

    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    QIcon icon(":/logo/icon.ico");
    this->setWindowIcon(icon);

#if defined(Q_OS_WIN)
    diskWriter = new DiskWriter_windows(this);
#elif defined(Q_OS_UNIX)
    diskWriter = new DiskWriter_unix(this);
#endif


    refreshDeviceList();

    connect(&manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(fileListReply(QNetworkReply*)));
    connect(ui->btInstall, SIGNAL(clicked()), this, SLOT(writeImageToDevice()));
    connect(ui->cbVersion, SIGNAL(currentTextChanged(QString)), this, SLOT(updateUI()));
    connect(ui->cbSDcards, SIGNAL(currentTextChanged(QString)), this, SLOT(updateUI()));
    connect(diskWriter, SIGNAL(bytesWritten(int)), this, SLOT(updateWriteProgress(int)));
    connect(ui->btAbout, SIGNAL(clicked()), this, SLOT(showAboutDialog()));


    // Create timer that refreshes the device list every second
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(refreshDeviceList()));
    timer->start(1000);

    isCancelled = false;

    setImageFileName("");

    QFile file("foo.xml");
    if (file.open(QFile::ReadOnly)) {
        QByteArray data = file.readAll();
        parseAndSetLinks(data);
    }
    else {
        updateLinks();
    }

}

Installer::~Installer()
{
    delete ui;
}

void Installer::refreshDeviceList()
{
    QStringList newDevices = diskWriter->getRemovableDeviceNames();
    if (newDevices != this->devices) {
        qDebug() << "Refreshing device list";
        this->devices = newDevices;
        ui->cbSDcards->clear();
        ui->cbSDcards->addItems(diskWriter->getUserFriendlyNamesRemovableDevices(devices));
        ui->cbSDcards->setCurrentIndex(ui->cbSDcards->count()-1);
    }
}

void Installer::cancel()
{
    if (!isCancelled)
        isCancelled = true;

    if (state == STATE_WRITING_IMAGE)
        diskWriter->cancelWrite();

    qDebug () << "Setting state idle! k";
    this->state = STATE_IDLE;
}

void Installer::updateWriteProgress(int i) {
    qDebug() << "Total image size:" << this->totalImageSize;
    qDebug() << "Written: " << i;
    this->percentage = (qreal)i/this->totalImageSize * 100;
    this->updateUI();
}

void Installer::showAboutDialog() {
    QString text = QString("Version %1\nBy Koenkk\nMade possible by Rasplex!").arg(installerVersion);
    QMessageBox::about(this, "About",text);
}

void Installer::parseAndSetLinks(const QByteArray &data)
{

    QXmlInputSource source;
    source.setData(data);

    bool ok = xmlReader.parse(source);
    if (!ok) {
        std::cout << "Parsing failed." << std::endl;
    }

    QXmlStreamReader reader(data);
    this->versions =  parseXML(reader);


    ui->cbVersion->clear();

    foreach (version v, versions) {
        qDebug() << "lasjdfklasdjklfajslkf";
        ui->cbVersion->addItem(v.name);
        ui->cbVersion->setCurrentIndex(0);
    }
}

void Installer::saveAndUpdateProgress(QNetworkReply *reply)
{
    qlonglong first, last, total;
    qlonglong contentLength = reply->header(QNetworkRequest::ContentLengthHeader).toLongLong();
    QByteArray contentRange = reply->rawHeader("Content-Range");

    // Sanity check
    if (contentRange.isEmpty()) {
        reset();
        return;
    }

    // Do some magic
    extractByteOffsetsFromContentLength(first, last, total, QString(contentRange));

    // Save data
    imageFile.seek(first);
    imageFile.write(reply->readAll());
    bytesDownloaded += contentLength;

    // Update progress bar
    this->percentage = (qreal)bytesDownloaded/total * 100;
    this->updateUI();
    qDebug() << bytesDownloaded << "/" << total << "=" << (qreal)bytesDownloaded/total * 100 << "%";
    qDebug() << this->state;
    if (this->percentage == 100) {
        // Done!
        this->state = STATE_IDLE;
        this->writeImageToDevice();
    }
}

void Installer::extractByteOffsetsFromContentLength(qlonglong &first, qlonglong &last, qlonglong &total, QString s)
{
    // Remove unit (assume bytes)
    int idx = s.indexOf(' ');
    s.remove(0, idx+1);

    // Find first
    idx = s.indexOf('-');
    first = s.left(idx).toLongLong();
    s.remove(0, idx+1);

    // Find last
    idx = s.indexOf('/');
    last = s.left(idx).toLongLong();
    s.remove(0, idx+1);

    // Total
    total = s.toLongLong();
}

void Installer::updateUI() {
    if (this->state == STATE_GETTING_LINKS) {
        this->setWindowTitle("Connecting...");
        this->ui->cbSDcards->setEnabled(false);
        this->ui->cbVersion->setEnabled(false);
        this->ui->lbSelectSD->setEnabled(false);
        this->ui->lbSelectVersion->setEnabled(false);
        this->ui->btInstall->setEnabled(false);
        return;
    } else {
        this->ui->cbSDcards->setEnabled(true);
        this->ui->cbVersion->setEnabled(true);
        this->ui->lbSelectSD->setEnabled(true);
        this->ui->lbSelectVersion->setEnabled(true);
        this->setWindowTitle("XBian installer");
    }

    QString selectedVersion = ui->cbVersion->itemText(ui->cbVersion->currentIndex());
    QString selectedSDCard = ui->cbSDcards->itemText(ui->cbSDcards->currentIndex());

    if (selectedVersion == "" || selectedSDCard == "") {
        ui->btInstall->setEnabled(false);
    } else {
        ui->btInstall->setEnabled(true);
    }

    switch (state) {
    case STATE_IDLE: ui->btInstall->setText("Install");
        break;
    case STATE_GETTING_URL:ui->btInstall->setText("Preparing download...");
        break;
    case STATE_DOWNLOADING_IMAGE: ui->btInstall->setText(QString("Downloading (%1%), press to cancel").arg(this->percentage));
        break;
    case STATE_WRITING_IMAGE: ui->btInstall->setText(QString("Installing (%1%), press to cancel").arg(this->percentage));
        break;
    case STATE_GETTING_LINKS: ui->btInstall->setText("Preparing download...");
        break;
    }
}

QByteArray Installer::rangeByteArray(qlonglong first, qlonglong last)
{
    return QByteArray("bytes=" + QByteArray::number(first) + "-" + QByteArray::number(last));
}

QNetworkRequest Installer::createRequest(QUrl &url, qlonglong first, qlonglong last)
{
    QNetworkRequest req(url);
    QByteArray range = rangeByteArray(first, last);
    qDebug() << range;
    req.setAttribute(QNetworkRequest::HttpPipeliningAllowedAttribute, true);
    req.setRawHeader("Range", range);
    req.setRawHeader("User-Agent", "Wget/1.14 (linux-gnu)");
    return req;
}

// From http://www.gamedev.net/topic/591402-gzip-uncompressed-file-size/
// Might not be portable!
unsigned int Installer::getUncompressedImageSize()
{
    FILE					*file;
    unsigned int			len;
    unsigned char			bufSize[4];
    unsigned int			fileSize;

    file = fopen(imageFileName.toStdString().c_str(), "rb");
    if (file == NULL)
        return 0;

    if (fseek(file, -4, SEEK_END) != 0)
        return 0;

    len = fread(&bufSize[0], sizeof(unsigned char), 4, file);
    if (len != 4) {
        fclose(file);
        return 0;
    }

    fileSize = (unsigned int) ((bufSize[3] << 24) | (bufSize[2] << 16) | (bufSize[1] << 8) | bufSize[0]);
    qDebug() << "Uncompressed FileSize:" << fileSize;

    fclose(file);
    return fileSize;
}

void Installer::setImageFileName(QString filename)
{
    if (imageFile.isOpen()) {
        qDebug() << "Tried to change filename while imageFile was open!";
        return;
    }
    imageFileName = filename;
    imageFile.setFileName(imageFileName);

    int idx = filename.lastIndexOf('/');
    if (idx > 0) {
        filename.remove(0, idx+1);
    }
}

void Installer::updateLinks()
{
    state = STATE_GETTING_LINKS;
    this->updateUI();

    QUrl url(sourceForgeRSS);
    manager.get(QNetworkRequest(url));
}

void Installer::downloadImage(QNetworkReply *reply)
{
    // TODO: Sanity checks!
    state = STATE_DOWNLOADING_IMAGE;
    qlonglong first, last, total;
    qlonglong contentLength = reply->header(QNetworkRequest::ContentLengthHeader).toLongLong();
    QByteArray contentRange = reply->rawHeader("Content-Range");

    // Do some magic. \todo Make it not report error on uncompressed iages
    extractByteOffsetsFromContentLength(first, last, total, QString(contentRange));

    // This is the first valid packet, save it!
    qDebug() << "Final url:" << downloadUrl << total;
    if (!imageFile.isOpen() && !imageFile.open(QFile::ReadWrite)) {
        return;
    }

    imageFile.write(reply->readAll());
    bytesDownloaded = contentLength;

    while (last <= total && ! isCancelled) {
        manager.get(createRequest(downloadUrl, last+1, (last+CHUNKSIZE >= total ? total-1 : last+CHUNKSIZE)));
        last += CHUNKSIZE;
    }
}

void Installer::reset()
{
    qDebug () << "Setting state idle! j";
    state = STATE_IDLE;
    bytesDownloaded = 0;
    if (imageFile.isOpen()) {
        imageFile.close();
    }
    //ui->writeButton->setEnabled( !ui->fileNameLabel->text().isEmpty());
    ui->cbSDcards->setEnabled(true);
    isCancelled = false;
}

void Installer::fileListReply(QNetworkReply *reply)
{
    this->updateUI();
    if (isCancelled) {
        isCancelled = false;
        this->percentage = 0;
    }

    if(reply->error() == QNetworkReply::NoError)
    {
        QUrl redirectionUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
        int responseCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toUInt();

        switch (state) {
        case STATE_GETTING_LINKS:
            if (responseCode == RESPONSE_OK && reply->isReadable()) {
                parseAndSetLinks(reply->readAll());
            }
            qDebug () << "Setting state idle! l";
            this->state = STATE_IDLE;
            this->updateUI();
            reset();
            break;
        case STATE_GETTING_URL:
            this->updateUI();
            if (redirectionUrl.isValid()) {
                downloadUrl = redirectionUrl;
                QNetworkRequest request = reply->request();
                request.setUrl(redirectionUrl);
                manager.get(request);
                qDebug() << "Redirected to:" << redirectionUrl;
                break;
            }

            // Start pipelined download
            downloadImage(reply);
            break;
        case STATE_DOWNLOADING_IMAGE:
            this->updateUI();
            switch (responseCode) {
            case RESPONSE_FOUND:
            case RESPONSE_REDIRECT:
                // Shouldn't happen!
                break;
            case RESPONSE_OK:
                // Probably a small file
                imageFile.write(reply->readAll());
                qDebug() << "Respone OK";
                break;
            case RESPONSE_PARTIAL:
                saveAndUpdateProgress(reply);
                break;
            default:
                qDebug() << "Unhandled reply:" << responseCode;
                break;
            }
            break; // downloading image
        default:
            break;
        }
    }

    reply->deleteLater();
}

void Installer::getImageFileNameFromUser()
{
    QString filename = QFileDialog::getOpenFileName(this);
    if (filename.isNull()) {
        return;
    }
    setImageFileName(filename);
    ui->btInstall->setEnabled(true);
    qDebug() << imageFileName;
}

void Installer::writeImageToDevice()
{
    // Check if there is some progress happening, if so this button is a cancel button
    if (this->state != this->STATE_IDLE) {
        this->cancel();
        this->updateUI();
        return;
    }

    // Get the image file name of the version which the user want to install
    QString selectedImage = versions.at(ui->cbVersion->currentIndex()).fileName;
    setImageFileName(selectedImage);
    version ver = versions.at(ui->cbVersion->currentIndex());


    // Check if the user already downloaded the image
    if (!imageFile.exists()) {
        QString selectedVersionName = ui->cbVersion->itemText(ui->cbVersion->currentIndex());
        QMessageBox::StandardButton confirmDownload = QMessageBox::warning(this, tr("Download XBian?"),
                                                              selectedVersionName + " has not been downloaded yet,\n"
                                                              "Do you want to download it now?",
                                                              QMessageBox::Yes | QMessageBox::No,
                                                              QMessageBox::No);
        // Check if the user want to download the image, if not return
        if (confirmDownload != QMessageBox::Yes) return;

        // The user has not downloaded the image, ask him if we have to download it
        state = STATE_GETTING_URL;
        this->updateUI();

        QString link = ui->cbVersion->itemData(ui->cbVersion->currentIndex()).toString();
        // Try to find file name in url
        int idx = link.lastIndexOf('/');
        if (idx > 0) {
            QString newFileName = link;
            setImageFileName(newFileName.remove(0, idx+1));
        }

        QUrl url(ver.downloadLink + "/download");
        qDebug() << url.toString();
        manager.get(createRequest(url, 0, CHUNKSIZE));
        return;
    }

    this->updateUI();

    QMessageBox::StandardButton ok = QMessageBox::warning(this, tr("Are you sure?"),
                                                          "Installing XBian to your SD card will delete all data on the selected SD card.\n\nWould you like to continue?",
                                                          QMessageBox::Yes | QMessageBox::No,
                                                          QMessageBox::No);


    if (ok != QMessageBox::Yes) {
        return;
    }


    // Check MD5
    QFileInfo fileInfo(imageFile);
    QString filename(fileInfo.absolutePath());
    qDebug() << filename;


    if (!ver.checkMD5(imageFile)) {
        qDebug() << "MD5 check failed!";
        QMessageBox::StandardButton verifyimage = QMessageBox::warning(this, tr("Warning!"),
                                                              "The downloaded image was unsuccessfully verified. Do you want to delete the image and try downloading it again?",
                                                              QMessageBox::Yes | QMessageBox::No,
                                                              QMessageBox::No);
        if (verifyimage == QMessageBox::Yes) {
            imageFile.remove();
            this->writeImageToDevice();
        }

        return;
    }

    this->percentage = 0;
    this->totalImageSize = this->getUncompressedImageSize();

    // TODO: make portable
    QString destination = this->devices.at(ui->cbSDcards->currentIndex());

    this->updateUI();

    if (destination.isNull()) {
        return;
    }

    // DiskWriter will re-open the image file.
    if (imageFile.isOpen()) {
        imageFile.close();
    }



    this->state = this->STATE_WRITING_IMAGE;
    if (diskWriter->open(destination) < 0) {
        qDebug() << "Failed to open output device";
        QString message = QString("Failed to open %1, are you sure the SD cards hardware lock is off?").arg(destination);
        QMessageBox::StandardButton success = QMessageBox::warning(this, tr("Error!"), message,QMessageBox::Ok);
        return;
    }


    if (!diskWriter->writeCompressedImageToRemovableDevice(ver.fileName)) {
        qDebug() << "Writing failed";
        reset();
        return;
    }

    if (!isCancelled) {
        QString message = "XBian has been succesfully installed on your SD card, you can now plug your SD card into your Raspberry Pi";
        QMessageBox::StandardButton success = QMessageBox::warning(this, tr("Installation succesfull!"), message,QMessageBox::Ok);
        qDebug () << "Setting state idle! m ";
        this->state = this->STATE_IDLE;
        this->updateUI();
        qDebug() << "Writing done!";
    }
}

QList<version> Installer::parseXML(QXmlStreamReader& xml) {
    QList<version> vers;
    qDebug() << "parsexml";
    while (!xml.atEnd() && !xml.hasError()) {
         QXmlStreamReader::TokenType token = xml.readNext();

         if(token == QXmlStreamReader::StartDocument) continue;

         if(token == QXmlStreamReader::StartElement) {
            if(xml.name() == "entry") {
                version v = this->parseVersion(xml);
                if (v.downloadLink != "") {
                    vers.append(v);

                }


            }
        }

    }

    xml.clear();
    return vers;
}

version Installer::parseVersion (QXmlStreamReader& xml) {
     QString downloadLink;
     QString md5;


     while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "entry")) {
         xml.readNext();
         if(xml.tokenType() == QXmlStreamReader::StartElement) {
            if(xml.name() == "link") {
                QXmlStreamAttributes atr = xml.attributes();

                if (atr.hasAttribute("href")) {
                    downloadLink = atr.value("href").toString();
                    if (!downloadLink.contains("release") || !downloadLink.contains(".img.gz")) {
                        downloadLink = "";
                    }
                }
             }


            if (xml.name() == "hash") {
                xml.readNext();
                md5 = xml.text().toString();
            }
        }
    }



     if (downloadLink != "" && md5 != "") {
        version v(downloadLink, md5);
        qDebug() << v.downloadLink;
        qDebug() << v.fileName;
        qDebug() << v.name;
        return v;
     }

      version v("","");
      return v;
}
