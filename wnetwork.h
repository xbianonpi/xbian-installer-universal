#ifndef WNETWORK_H
#define WNETWORK_H

#include <QString>

class wNetwork
{
public:
    enum wProtection {
        OPEN,
        WPA,
        WEP
    };

    wNetwork(QString name, wProtection protection, QString pass);

    QString wirelessNetworkName;
    wProtection wirelessProtection;
    QString wirelessNetworkPass;
};

#endif // WNETWORK_H
