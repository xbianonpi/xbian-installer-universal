#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

#define installer_version "Version 1.21"


class rpi_or_cubox_class
{
static QString rpi_or_cubox;
public:
void setVal(const QString& rpi_cubox) {
        rpi_or_cubox = rpi_cubox;
    }
QString getVal() const {
return rpi_or_cubox;
}
};


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:

    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
