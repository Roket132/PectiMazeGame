#include "serversettings.h"
#include "appsettings.h"

ServerSettings::ServerSettings() : server(nullptr) {
}

ServerSettings::~ServerSettings() {
}

void ServerSettings::sendSettingsToClient(QTcpSocket *socket) {
    ClientInfo *info = getClientInfoBySocket(socket);
    Player *player = info->getPlayer();
    QString settings = QStringLiteral("settings %1 %2 %3").arg(info->getAvatarType())
            .arg(player->isExtraLight()).arg(player->getCntPectiArrow());
    server->sendToClient(socket, settings);
    if (player->isFight()) {
        auto task = archive.getTask(info->getCurrentTask(false) - 1);
        server->sendToClient(socket, QString("Task %1").arg(pars::prepareTaskForSend(task)));
        server->sendToClient(socket, QStringLiteral("Action attack %1").arg(player->getEnemyDifficulty()));
    }
}

void ServerSettings::createTasksArchive() {
    AppSettings &settings = AppSettings::getAppSettings();
    for (auto path : *settings.getPathForTasks()) {
        archive.readFile(path.toStdString());
    }
}

ServerSettings &ServerSettings::getServerSettings() {
    static ServerSettings instance;
    return instance;
}

void ServerSettings::startServer(fs::path path) {
    server = new Server(1337);
    maze = new Maze(path);

    createTasksArchive();

    bool c1 = connect(server, SIGNAL(signalRegNewClient(QString, QTcpSocket*)), this, SLOT(slotRegNewClient(QString, QTcpSocket*)));
    bool c2 = connect(server, SIGNAL(signalEnterClient(QString, QTcpSocket*)), this, SLOT(slotEnterClient(QString, QTcpSocket*)));
    connect(server, SIGNAL(signalMovePlayer(QString, QTcpSocket*)), this, SLOT(slotMovePlayer(QString, QTcpSocket*)));
    connect(server, SIGNAL(signalUseInventory(QString, QTcpSocket*)), this, SLOT(slotUseInventory(QString, QTcpSocket*)));
    connect(server, SIGNAL(signalClientExit(QString, QTcpSocket*)), this, SLOT(slotClientExit(QString, QTcpSocket*)));
    connect(server, SIGNAL(signalCheckAnswer(QString, QTcpSocket*)), this, SLOT(slotCheckAnswer(QString, QTcpSocket*)));
    Q_ASSERT(c1); Q_ASSERT(c2);

}

void ServerSettings::closeServer() {
    delete server;
    delete maze;
    this->disconnect();
}

Maze* ServerSettings::createMaze(std::experimental::filesystem::__cxx11::path path) {
    if (fs::is_empty(path)) {
        maze = nullptr;
        return nullptr;
    }
    return new Maze(path);
}

void ServerSettings::slotRegNewClient(QString str, QTcpSocket* socket) {
    std::pair<int, int> stPlace = maze->getFreeStartPlace();
    ClientInfo* newClient = new ClientInfo(str, socket, stPlace.first, stPlace.second, static_cast<int>(clients.size()));
    clients.push_back(newClient);
    server->sendToClient(socket, "success;");
    emit signalPlayerConnected(newClient);
}

void ServerSettings::slotEnterClient(QString str, QTcpSocket* socket) {
    std::vector<QString> req = pars::parseRequest(str);
    bool countL = false;
    bool countP = false;
    ClientInfo* client = nullptr;
    for (auto it : clients) {
        if (it->getLogin() == req[1]) {
            countL = true;
            if (it->getPassword() == req[2]) {
                countP = true;
                client = it;
            }
        }
        if (countL && countP)
            break;
        else
            countL = countP = false;
    }

    if (countL && countP) {
        client->setSocket(socket);
        server->sendToClient(socket, "success;");
        sendSettingsToClient(socket);
        emit signalPlayerConnected(client);
    } else {
        server->sendToClient(socket, "faild;");
    }

}

void ServerSettings::slotMovePlayer(QString str, QTcpSocket *socket) {
    Player* player = getPlayerBySocket(socket);
    if (!player->canMove()) return;

    std::vector<QString> req = pars::parseRequest(str);
    int dx = req[1].toInt();
    int dy = req[2].toInt();
    player->move(dx, dy);
    doCellAction(player, socket);
}

void ServerSettings::slotUseInventory(QString str, QTcpSocket *socket) {
    Player* player = getPlayerBySocket(socket);
    std::vector<QString> req = pars::parseRequest(str);
    if (req[1] == "pecti_arrow") {
        if (getPlayerBySocket(socket)->usePectiArrow()) {
            maze->setPectiArrow(player->getPosition().first, player->getPosition().second);
        }
        server->sendToClient(socket, "HUD del pecti_arrow 1");
    }
}

void ServerSettings::slotClientExit(QString str, QTcpSocket *socket) {
    emit signalPlayerDisconnected(getClientInfoBySocket(socket));
}

void ServerSettings::slotCheckAnswer(QString str, QTcpSocket *socket) {
    std::vector<QString> req = pars::parseRequest(str, 2);
    auto split = pars::splitTask(req[1]);
    if (archive.checkAnswer(split.second.toStdString(), split.first.toStdString())) {
        server->sendToClient(socket, QString("Action answer success %1").arg(split.first));
        Player* player = getPlayerBySocket(socket);
        player->setFight(false, 0);
        auto enemyPos = player->getCurEnemyPos();
        maze->killEnemy(enemyPos.first, enemyPos.second);
        doCellAction(player, socket);
    } else {
        server->sendToClient(socket, "Action answer faild");
    }
}

Maze* ServerSettings::getMaze() {
    return maze;
}

QString ServerSettings::getMapPlayerBySocket(QTcpSocket *socket) {
    for (auto it : clients) {
        if (it->getTcpSocket() == socket) {
            std::pair<int, int> pl = it->getPlayer()->getPosition();
            return getMapPlayerByPlace(pl.first, pl.second, it->getPlayer()->isExtraVis());
        }
    }
    return "map 0 0";
}


QString ServerSettings::getMapPlayerByPlace(int x, int y, bool extra) {
    QString ans = QStringLiteral("map %1 %2").arg(5).arg(5);
    for (int i = x - 2/*??*/; i <= x + 2; i++) {
        for (int j = y - 2; j <= y + 2; j++) {
            if (!extra && (abs(x - i) > 1 || abs(y - j) > 1)) {
                ans += " fog";
                continue;
            }
            if (i < 0 || j < 0 || i >= maze->height() || j >= maze->width()) {
                ans += " -1";
            } else if (i == x && j == y) {
                ans += " P";
            } else {
                ans += " " + maze->getTypeObject(static_cast<size_t>(i), static_cast<size_t>(j));
            }
        }
    }
    return ans;
}

std::shared_ptr<Task> ServerSettings::getNextTask(QTcpSocket *socket) {
    ClientInfo *cl = getClientInfoBySocket(socket);
    return archive.getTask(cl->getCurrentTask(true));
}


void ServerSettings::doCellAction(Player *player, QTcpSocket *socket) {
    player->action();

    std::pair<size_t, size_t> pos = player->getPosition();
    MazeObject* obj = maze->getMazeObject(pos.first, pos.second);

    QString type = obj->getTypeObject();

    if (type == "lamp") {
        player->setExtraLight(true);
        maze->removeObjectFromCell(pos.first, pos.second);
        server->sendToClient(socket, "HUD add lamp 1;");
    } else if (type == "light_source") {
        if (player->isExtraLight()) {
            player->setExtraVision(10);
        }
    } else if (type == "pecti_arrow") {
        player->takePectiArrow();
        maze->removeObjectFromCell(pos.first, pos.second);
        server->sendToClient(socket, "HUD add pecti_arrow 1;");
    } else if (maze->enemyAttack(pos.first, pos.second).first) {
        auto enemy = maze->enemyAttack(pos.first, pos.second);
        player->setFight(true, static_cast<size_t>(enemy.first));
        player->setCurEnemyPos({enemy.second.first, enemy.second.second});
        auto task = getNextTask(socket);
        server->sendToClient(socket, QStringLiteral("Task %1").arg(pars::prepareTaskForSend(task)));
        server->sendToClient(socket, QStringLiteral("Action attack %1").arg(enemy.first));
    }

}

Player* ServerSettings::isPlayer(int x, int y) {
    for (auto it : clients) {
        if (it->isPlayerPlace(x, y)) {
            return it->getPlayer();
        }
    }
    return nullptr;
}

Player *ServerSettings::getPlayerBySocket(QTcpSocket *socket) {
    for (auto it : clients) {
        if (it->getTcpSocket() == socket) {
            return it->getPlayer();
        }
    }
    return nullptr;
}

ClientInfo *ServerSettings::getClientInfoBySocket(QTcpSocket *socket) {
    for (auto it : clients) {
        if (it->getTcpSocket() == socket) {
            return it;
        }
    }
    return nullptr;
}
