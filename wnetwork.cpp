#include "wnetwork.h"

wNetwork::wNetwork(QString name, wProtection protection, QString pass) {
    this->wirelessNetworkName = name;
    this->wirelessProtection = protection;
    this->wirelessNetworkPass = pass;
}
