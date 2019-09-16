#include "clientsettings.h"

#include <iostream>
#include "settingswindow.h"

ClientSettings &ClientSettings::getClientSettings() {
    static ClientSettings instance;
    return instance;
}

ClientSettings::ClientSettings() : maze_mutex(new std::mutex), hud_mutex(new std::mutex) {
}

ClientSettings::~ClientSettings() {
    delete clientMaze;
    delete client;
}

void ClientSettings::startClient(QString login_, QString password_, bool old) {
    // save input settings
    login = login_;
    password = password_;

    createEmptyMaze();
    clientHUD = new HUD();

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
    std::lock_guard<std::mutex> lg(*maze_mutex);
    return clientMaze;
}

HUD *ClientSettings::getHUD() {
    std::lock_guard<std::mutex> lg(*hud_mutex);
    return clientHUD;
}

void ClientSettings::clientConnects() {
    connect(client, SIGNAL(signalSetMap(QString)), this, SLOT(slotSetMap(QString)));
    connect(client, SIGNAL(signalHUDUpdate(QString)), this, SLOT(slotHUDUpdate(QString)));
}

void ClientSettings::slotSetMap(QString map) {
    std::lock_guard<std::mutex> lg(*maze_mutex);
    if (clientMaze) delete clientMaze;
    clientMaze = new Maze(map);
}

void ClientSettings::slotHUDUpdate(QString req) {
    std::lock_guard<std::mutex> lg(*hud_mutex);
    clientHUD->parseRequest(req);
}
