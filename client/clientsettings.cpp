#include "clientsettings.h"

#include <iostream>


ClientSettings &ClientSettings::getClientSettings() {
    static ClientSettings instance;
    return instance;
}

ClientSettings::ClientSettings() {

}

ClientSettings::~ClientSettings() {
    delete clientMaze;
    delete client;
}

void ClientSettings::startNewClient(QString login_, QString password_) {
    login = login_;
    password = password_;
    client = new Client("localhost", 1337);
    client->sendToServer(QStringLiteral("reg %1 %2;").arg(login_).arg(password_));
    std::cerr << "otpravil reg" << std::endl;
    clientConnects();
}

void ClientSettings::startOldClient(QString login_, QString password_) {
    login = login_;
    password = password_;
    client = new Client("localhost", 1337);
    client->sendToServer(QStringLiteral("enter %1 %2;").arg(login_).arg(password_));
    std::cerr << "otpravil enter" << std::endl;
    clientConnects();
}

void ClientSettings::closeClient() {
    if (client != nullptr) delete client;
}

Client *ClientSettings::getClient() {
    return client;
}

void ClientSettings::createEmptyMaze() {
    if (clientMaze != nullptr) delete clientMaze;
    clientMaze = new Maze(QString("map 5 5 # # # # # # # # # # # # # # # # # # # # # # # # #"));

}

Maze *ClientSettings::getMaze() {
    return clientMaze;
}

void ClientSettings::clientConnects() {
    connect(client, SIGNAL(signalSetMap(QString)), this, SLOT(slotSetMap(QString)));
}

void ClientSettings::slotSetMap(QString map) {
    if (clientMaze) delete clientMaze;
    clientMaze = new Maze(map);
}
