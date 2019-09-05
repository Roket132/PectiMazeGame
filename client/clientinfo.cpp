#include "clientinfo.h"

ClientInfo::ClientInfo(QString str, QTcpSocket* socket) {
    std::vector<QString> info = pars::parseRequest(str); // if reg then info has only 2(3) parametrs "type login password"
    login = info[1];
    password = info[2];
    pTcpSocket = socket;
}

QString ClientInfo::getLogin()
{
    return login;
}

QString ClientInfo::getPassword()
{
    return password;
}

void ClientInfo::setSocket(QTcpSocket *socket)
{
    pTcpSocket = socket;
}
