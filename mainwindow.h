#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include "version.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_btInstall_clicked();
    void fileIsReady(QNetworkReply* reply);
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void downloadFinished();
    void downloadReadyRead();
    void cancelDownload();

private:
    Ui::MainWindow *ui;
    void refreshDrives();
    void restoreImage(string image);
    void initXMLRequestFromWeb(QUrl url);
    void refreshUI();
    void downloadFile(QUrl url);
    void installVersion(version ver);


    QNetworkAccessManager manager;
        QFile *file;
        QString filename;
        QNetworkReply *reply;
        bool downloadRequestAborted;
        bool downloadInProgress;


};

#endif // MAINWINDOW_H
