#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>

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

private:
    Ui::MainWindow *ui;
    void refreshDrives();
    void restoreImage(string image);
    void initXMLRequestFromWeb(QUrl url);
    void refreshUI();
};

#endif // MAINWINDOW_H
