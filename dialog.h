#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

// ***
#include <QUrl>
// ***

class sourceForgeURL
{
static QUrl sourceForgeURLtype;
public:
void setVal(const QUrl& sFurl) {
        sourceForgeURLtype = sFurl;
    }
QUrl getVal() const {
return sourceForgeURLtype;
}
};

#define sourceForgeRSS_release "http://sourceforge.net/projects/xbian/rss?path=/release"
#define sourceForgeRSS_testing "http://sourceforge.net/projects/xbian/rss?path=/testing"
// ***

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
