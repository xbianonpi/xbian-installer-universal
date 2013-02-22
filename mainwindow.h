#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void restoreImage(string image, string device);
};

#endif // MAINWINDOW_H
