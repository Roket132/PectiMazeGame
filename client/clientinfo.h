#ifndef CLIENTINFO_H
#define CLIENTINFO_H

#include "parsing/parsingtools.h"
#include "engine/Objects/player.h"
#include "maze.h"

#include <QString>
#include <QTcpSocket>

/*
 *
 * class for save client on server,
 * on client all settigns be kept in @clientsettings@
 * don't use this class, for save clientInfo on client
 *
 */

class ClientInfo {
public:
    ClientInfo(QString str, QTcpSocket* socket, int start_x, int start_y, int id_);
    ~ClientInfo();

    QString getLogin();
    QString getPassword();
    size_t getCurrentTask(bool increment);

    void setSocket(QTcpSocket* socket);

    bool isPlayerPlace(int x, int y);

    Player* getPlayer();
    size_t getAvatarType();
    const QTcpSocket* getTcpSocket();

private:
    int id;
    size_t avatarType;
    QString login;
    QString password;

    size_t currentTask;

    QTcpSocket* pTcpSocket;

private:
    Player* player;
};

#endif // CLIENTINFO_H
