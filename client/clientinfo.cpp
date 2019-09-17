#include "clientinfo.h"

ClientInfo::ClientInfo(QString str, QTcpSocket* socket, int start_x, int start_y, int id_) : id(id_) {
    std::vector<QString> info = pars::parseRequest(str); // if reg then info has only 2(3) parametrs "type login password"
    login = info[1];
    password = info[2];
    pTcpSocket = socket;
    player = new Player(QPixmap(":/res/image/image_40/man_1.jpg"));
    player->moveTo(start_x, start_y);
}

ClientInfo::~ClientInfo() {
    delete pTcpSocket;
    delete player;
}

QString ClientInfo::getLogin()
{
    return login;
}

QString ClientInfo::getPassword()
{
    return password;
}

void ClientInfo::setSocket(QTcpSocket *socket) {
    pTcpSocket = socket;
}

bool ClientInfo::isPlayerPlace(int x, int y) {
    std::pair<int, int> pl = player->getPosition();
    return (x == pl.first && y == pl.second);
}

Player* ClientInfo::getPlayer() {
    return player;
}

const QTcpSocket *ClientInfo::getTcpSocket()
{
    return pTcpSocket;
}
