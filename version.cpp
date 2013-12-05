#include "version.h"
#include <QCryptographicHash>

version::version(QString downloadLink, QString md5) {
    this->downloadLink = downloadLink.replace("/download","");
    this->md5 = md5;

    int index = this->downloadLink.lastIndexOf("/");
    this->fileName = downloadLink.mid(index + 1);
    this->name = fileName;
    this->name.replace(".img.gz","");
    this->name.replace("_"," ");
}

bool version::checkMD5(QFile& file) {
    if(file.open(QIODevice::ReadOnly)) {
        QCryptographicHash* hash;

                QString fileHash = hash->hash(file.readAll(),QCryptographicHash::Md5).toHex();
                file.close();
                if (this->md5 == fileHash) return true;
    }

    return false;
}
