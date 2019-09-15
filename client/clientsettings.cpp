#include "clientsettings.h"

#include <iostream>
#include "settingswindow.h"

ClientSettings &ClientSettings::getClientSettings() {
    static ClientSettings instance;
    return instance;
}

ClientSettings::ClientSettings() {
    mutex_ = new std::mutex;
}

ClientSettings::~ClientSettings() {
    delete clientMaze;
    delete client;
}

void ClientSettings::startClient(QString login_, QString password_, bool old) {
    mutex_ = new std::mutex;

    // save input settings
    login = login_;
    password = password_;

    // start client;

    client = new Client("localhost", 1337);
    client->sendToServer(QStringLiteral("%1 %2 %3;").arg(old ? "enter" : "reg").arg(login_).arg(password_));
    std::cerr << "otpravil old??" << " " << (old ? "enter" : "reg") << std::endl;
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
    std::lock_guard<std::mutex> lg(*mutex_);
    return clientMaze;
}

void ClientSettings::clientConnects() {
    connect(client, SIGNAL(signalSetMap(QString)), this, SLOT(slotSetMap(QString)));
}

void ClientSettings::slotSetMap(QString map) {
    std::lock_guard<std::mutex> lg(*mutex_);
    if (clientMaze) delete clientMaze;
    clientMaze = new Maze(map);
}
