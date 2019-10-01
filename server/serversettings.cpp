#include "serversettings.h"
#include "appsettings.h"

#include <QFile>
#include <QTemporaryDir>

#include "actions/mazeactions.h"
#include "actions/inventoryactions.h"

ServerSettings::ServerSettings() : server(nullptr) {
}

ServerSettings::~ServerSettings() {
}

void ServerSettings::sendSettingsToClient(QTcpSocket *socket) {
    ClientInfo *info = getClientInfoBySocket(socket);
    Player *player = info->getPlayer();
    QString settings = QStringLiteral("settings %1 %2 %3 %4 %5 %6 %7 %8 %9 %10").arg(player->getExtraVisTimer())
            .arg(player->getExtraVision()).arg(player->getExtraLight()).arg(player->getCntPectiArrow())
            .arg(player->isFight() ? 1 : 0).arg(player->getEnemyDifficulty())
            .arg(player->getCurEnemyPos().first).arg(player->getCurEnemyPos().second).arg(player->getScore()).arg(info->getAvatarType());
    server->sendToClient(socket, settings);
    if (player->isFight()) {
        auto task = archiveEnemyTasks.getTask(info->getCurrentEnemyTask(player->getEnemyDifficulty(), false) - 1, player->getEnemyDifficulty());
        server->sendToClient(socket, QString("Task add enemy %1 %2").arg(player->getEnemyDifficulty()).arg(pars::prepareTaskForSend(task)));
        server->sendToClient(socket, QStringLiteral("Action attack %1").arg(player->getEnemyDifficulty()));
    }
    if (player->getCntPectiArrow() > 0) {
        auto task = archiveArrowTasks.getTask(info->getCurrentArrowTask(1, false) - 1, 1);
        server->sendToClient(socket, QString("Task add arrow %1 %2").arg(1).arg(pars::prepareTaskForSend(task)));
    }
}

void ServerSettings::createTasksArchives() {
    AppSettings &settings = AppSettings::getAppSettings();
    QTemporaryDir tempDir;
    if (tempDir.isValid()) {
        const QString enemyFile = tempDir.path() + "/enemyTasks.txt";
        const QString arrowFile = tempDir.path() + "/arrowTasks.txt";
        if (QFile::copy(":/files/tasks/enemyTasks.txt", enemyFile)) {
            archiveEnemyTasks.readFile(enemyFile.toStdString());
        }
        if (QFile::copy(":/files/tasks/arrowTasks.txt", arrowFile)) {
            archiveArrowTasks.readFile(arrowFile.toStdString());
        }
    }
    for (auto path : *settings.getPathForEnemyTasks()) {
        archiveEnemyTasks.readFile(path.toStdString());
    }
    for (auto path : *settings.getPathForArrowTasks()) {
        archiveArrowTasks.readFile(path.toStdString());
    }
}

ServerSettings &ServerSettings::getServerSettings() {
    static ServerSettings instance;
    return instance;
}

void ServerSettings::startServer(fs::path path) {
    server = new Server(1337);
    maze = new Maze(path);

    createTasksArchives();

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
    emit signalAutoFocus();
    doCellAction(player, socket);
}

void ServerSettings::slotUseInventory(QString str, QTcpSocket *socket) {
    auto player = getPlayerBySocket(socket);
    std::vector<QString> req = pars::parseRequest(str);

    InventoryActions invActions(maze, player, socket, server);
    if (req[1] == "pecti_arrow") {
        invActions.useArrow([this, &player, &socket] {
            std::cerr << "kek" << std::endl;
            if (player->getCntPectiArrow() != 0) {
                sendNextArrowTask(socket);
            }
            server->sendToClient(socket, "HUD del pecti_arrow 1");
        });
    }
}

void ServerSettings::slotClientExit(QString str, QTcpSocket *socket) {
    emit signalPlayerDisconnected(getClientInfoBySocket(socket));
}

void ServerSettings::slotCheckAnswer(QString str, QTcpSocket *socket) {
    std::vector<QString> req = pars::parseRequest(str, 4);
    auto split = pars::splitTask(req[3]);
    auto *archive = (req[1] == "enemy" ? &archiveEnemyTasks : &archiveArrowTasks);
    if (archive->checkAnswer(split.second.toStdString(), split.first.toStdString(), req[2].toUInt())) {
        server->sendToClient(socket, QString("Action answer success %1 %2").arg(req[1]).arg(split.first));
        Player* player = getPlayerBySocket(socket);
        MazeActions actions(maze, player, socket, server);
        InventoryActions invActions(maze, player, socket, server);

        if (req[1] == "enemy") {
            actions.winUponEnemy(req[2].toUInt());
        } else if (req[1] == "arrow") {
            slotUseInventory("use pecti_arrow", socket);
        }
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

std::shared_ptr<Task> ServerSettings::getNextEnemyTask(QTcpSocket *socket, size_t lvl) {
    ClientInfo *cl = getClientInfoBySocket(socket);
    return archiveEnemyTasks.getTask(cl->getCurrentEnemyTask(lvl, true), lvl);
}

std::shared_ptr<Task> ServerSettings::getNextArrowTask(QTcpSocket *socket, size_t lvl) {
    ClientInfo *cl = getClientInfoBySocket(socket);
    return archiveArrowTasks.getTask(cl->getCurrentArrowTask(lvl, true), lvl);
}

void ServerSettings::doCellAction(Player *player, QTcpSocket *socket) {
    player->action();

    std::pair<size_t, size_t> pos = player->getPosition();
    MazeObject* obj = maze->getMazeObject(pos.first, pos.second);

    QString type = obj->getTypeObject();
    MazeActions actions(maze, player, socket, server);

    if (type == "lamp") {
        actions.takeLamp([this, &socket] {
            server->sendToClient(socket, "HUD add lamp 1;");
        });
    } else if (type == "light_source") {
        actions.turnOnLamp(10);
    } else if (type == "pecti_arrow") {
        actions.takeArrow([this, &player, &socket] {
            if (player->getCntPectiArrow() == 1) {
                sendNextArrowTask(socket);
            }
            server->sendToClient(socket, "HUD add pecti_arrow 1;");
        });
    } else if (maze->enemyAttack(pos.first, pos.second).first) {
        actions.enemyAttack([this, &socket, &pos] {
            auto enemy = maze->enemyAttack(pos.first, pos.second);
            sendNextEnemyTask(socket, static_cast<size_t>(enemy.first));
            server->sendToClient(socket, QStringLiteral("Action attack %1").arg(enemy.first));
        });
    }

}

Player* ServerSettings::isPlayer(size_t x, size_t y) {
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

void ServerSettings::sendNextArrowTask(QTcpSocket* socket, size_t lvl) {
    /*
     *  if client didn't has arrow, he need task.
     *  For next arrow tasks will be send automatically
     */
    auto task = getNextArrowTask(socket, lvl);
    server->sendToClient(socket, QStringLiteral("Task add arrow %1 %2").arg(lvl).arg(pars::prepareTaskForSend(task)));
}

void ServerSettings::sendNextEnemyTask(QTcpSocket *socket, size_t lvl) {
    auto task = getNextEnemyTask(socket, static_cast<size_t>(lvl));
    server->sendToClient(socket, QStringLiteral("Task add enemy %1 %2").arg(lvl).arg(pars::prepareTaskForSend(task)));
}
