#ifndef CLIENTINFO_H
#define CLIENTINFO_H

#include "parsing/parsingtools.h"
#include "engine/Objects/player.h"
#include "maze.h"

#include <QString>
#include <QTcpSocket>

class ClientInfo {
public:
    ClientInfo(QString str, QTcpSocket* socket, int start_x, int start_y);

    QString getLogin();
    QString getPassword();

    void setSocket(QTcpSocket* socket);

    bool isPlayerPlace(int x, int y);

    Player* getPlayer();

private:
    QString login;
    QString password;

    QTcpSocket* pTcpSocket;

private:
    Player* player;
};

#endif // CLIENTINFO_H
