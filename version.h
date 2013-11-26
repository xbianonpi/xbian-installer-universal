#ifndef VERSION_H
#define VERSION_H

#include <QString>
#include <QFile>

class version
{
public:
    version(QString downloadLink, QString md5);
    QString downloadLink;
    QString fileName;
    QString name;
    bool checkMD5(QFile& file);
private:
    QString md5;
};

#endif // VERSION_H
