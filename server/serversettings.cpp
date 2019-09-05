#include "serversettings.h"


ServerSettings::ServerSettings(fs::path path) : server(nullptr) {
    maze = createMaze(path);
}

ServerSettings &ServerSettings::getServerSettings(fs::path path) {
    static ServerSettings instance(path);
    return instance;
}

void ServerSettings::startServer() {
    server = new Server(1337);
    bool c1 = connect(server, SIGNAL(signalRegNewClient(QString, QTcpSocket*)), this, SLOT(slotRegNewPlayer(QString, QTcpSocket*)));
    bool c2 = connect(server, SIGNAL(signalEnterClient(QString, QTcpSocket*)), this, SLOT(slotEnterClient(QString, QTcpSocket*)));
    Q_ASSERT(c1);
}

Maze* ServerSettings::createMaze(std::experimental::filesystem::__cxx11::path path) {
    if (fs::is_empty(path)) {
        maze = nullptr;
        return nullptr;
    }
    return new Maze(path);
}

void ServerSettings::slotRegNewPlayer(QString str, QTcpSocket* socket) {
    ClientInfo* newClient = new ClientInfo(str, socket);
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

Maze* ServerSettings::getMaze() {
    return maze;
}
