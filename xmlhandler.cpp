#include "xmlhandler.h"
#include <QXmlStreamAttributes>

QList<version> xmlHandler::parseXML(QXmlStreamReader xml) {
    QList<version> versions;

    while (!xml.atEnd() && !xml.hasError()) {
         QXmlStreamReader::TokenType token = xml.readNext();

         if(token == QXmlStreamReader::StartDocument) continue;

         if(token == QXmlStreamReader::StartElement) {
            if(xml.name() == "entry") {
                version v = this->parseVersion(xml);
                if (v != NULL) {
                    versions.append(v);
                    xml.readNext();
                }
            }
        }
    }
}

version xmlHandler::parseVersion (QXmlStreamReader& xml) {
     QString downloadLink;
     QString md5;

     while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "entry")) {
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


            if (xml.name() == "media:hash") {
                md5 = xml.text();
            }
        }
    }

     qDebug() << downloadLink;
     qDebug() << md5;

     if (downloadLink == "" || md5 == "") {
        version v(downloadLink, md5);
        return v;
     }

     return NULL;
}
