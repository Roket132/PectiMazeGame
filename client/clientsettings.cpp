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

void ClientSettings::startClient(QString login_, QString password_, size_t avatarType, QString ip, bool old) {
    // save input settings
    login = login_;
    password = password_;

    createEmptyMaze();
    clientHUD = new HUD();

    // start client;

    client = new Client(ip, 1337);
    client->sendToServer(QStringLiteral("%1 %2 %3 %4;").arg(old ? "enter" : "reg").arg(login_).arg(password_).arg(avatarType));
    clientConnects();
}

void ClientSettings::closeClient() {
    archiveEnemyTasks.clear();
    archiveArrowTasks.clear();
    this->disconnect();
    client->disconnect();
}

Client *ClientSettings::getClient() {
    return client;
}


void ClientSettings::createEmptyMaze() {
    if (clientMaze != nullptr) delete clientMaze;
    clientMaze = new Maze(QString("map 5 5 # # # # # # # # # # # # # # # # # # # # # # # # #"));

}

std::shared_ptr<Task> ClientSettings::getNextEnemyTask(size_t lvl) {
    return archiveEnemyTasks.getNextTask(lvl);
}

std::shared_ptr<Task> ClientSettings::getNextArrowTask(size_t lvl) {
    return archiveArrowTasks.getNextTask(lvl);
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
    connect(client, SIGNAL(signalSetSettings(QString)), this, SLOT(slotSetSettings(QString)));
    connect(client, SIGNAL(signalAction(QString)), this, SLOT(slotAction(QString)));
    connect(client, SIGNAL(signalAddTask(QString)), this, SLOT(slotAddTask(QString)));
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

void ClientSettings::slotSetSettings(QString req) {
    clientHUD->restoreInventory(req);
}

void ClientSettings::slotAction(QString req_) {
    std::vector<QString> req = pars::parseRequest(req_, 5);
    if (req[1] == "attack") {
        emit signalAttack(req[2].toInt());
    } else if (req[1] == "answer") {
        if (req[2] == "success") {
            emit signalAnswerSuccessful(req[3], req[4]);
        } else {
            emit signalAnswerIncorrect();
        }
    }
}

void ClientSettings::slotAddTask(QString req_) {
    std::vector<QString> req = pars::parseRequest(req_, 5);
    if (req[1] == "add") {
        auto split = pars::splitTask(req[4]);
        auto lvl = req[3].toStdString();
        if (req[2] == "enemy")
            archiveEnemyTasks.addTask(std::make_shared<Task>(Task(split.first.toStdString(), split.second.toStdString(), lvl)));
        else if (req[2] == "arrow")
            archiveArrowTasks.addTask(std::make_shared<Task>(Task(split.first.toStdString(), split.second.toStdString(), lvl)));
    }
}
