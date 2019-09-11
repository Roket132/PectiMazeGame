#include "serversettings.h"

/*
 * TODO
 * 1. getMapPlayer By Place, need add demension
 */

ServerSettings::ServerSettings(fs::path path) : server(nullptr) {
    maze = createMaze(path);
}

ServerSettings::~ServerSettings() {
    delete server;
    delete maze;
}

ServerSettings &ServerSettings::getServerSettings(fs::path path) {
    static ServerSettings instance(path);
    return instance;
}

void ServerSettings::startServer() {
    server = new Server(1337);
    bool c1 = connect(server, SIGNAL(signalRegNewClient(QString, QTcpSocket*)), this, SLOT(slotRegNewClient(QString, QTcpSocket*)));
    bool c2 = connect(server, SIGNAL(signalEnterClient(QString, QTcpSocket*)), this, SLOT(slotEnterClient(QString, QTcpSocket*)));
    connect(server, SIGNAL(signalMovePlayer(QString, QTcpSocket*)), this, SLOT(slotMovePlayer(QString, QTcpSocket*)));
    Q_ASSERT(c1);
}

void ServerSettings::closeServer() {
    if (server != nullptr) delete server;
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
}

void ServerSettings::slotEnterClient(QString str, QTcpSocket* socket)
{
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
    }

    if (countL && countP) {
        client->setSocket(socket);
        server->sendToClient(socket, "success;");
    } else {
        server->sendToClient(socket, "faild;");
    }

}

void ServerSettings::slotMovePlayer(QString str, QTcpSocket *socket) {
    Player* player = getPlayerBySocket(socket);
    std::vector<QString> req = pars::parseRequest(str);
    int dx = req[1].toInt();
    int dy = req[2].toInt();
    player->move(dx, dy);
    doCellAction(player);
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

void ServerSettings::doCellAction(Player *player) {
    player->action();

    std::pair<size_t, size_t> pos = player->getPosition();
    MazeObject* obj = maze->getMazeObject(pos.first, pos.second);

    QString type = obj->getTypeObject();

    if (type == "lamp") {
        player->setExtraLight(true);
    } else if (type == "light_source") {
        if (player->isExtraLight()) {
            player->setExtraVision(10); // TODO set dif time
        }
    }

}
