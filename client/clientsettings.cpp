#include "clientsettings.h"

#include <iostream>

ClientSettings::ClientSettings() {

}

ClientSettings &ClientSettings::getClientSettings() {
    static ClientSettings instance;
    return instance;
}

void ClientSettings::startNewClient(QString login_, QString password_) {
    login = login_;
    password = password_;
    client = new Client("localhost", 1337);
    client->sendToServer(QStringLiteral("reg %1 %2;").arg(login_).arg(password_));
    std::cerr << "otpravil reg" << std::endl;

}

void ClientSettings::startOldClient(QString login_, QString password_) {
    login = login_;
    password = password_;
    client = new Client("localhost", 1337);
    client->sendToServer(QStringLiteral("enter %1 %2;").arg(login_).arg(password_));
    std::cerr << "otpravil enter" << std::endl;
}

const Client *ClientSettings::getClient()
{
    return client;
}
