#ifndef CLIENTINFO_H
#define CLIENTINFO_H

#include "parsing/parsingtools.h"
#include "engine/Objects/player.h"
#include "maze.h"

#include <QString>
#include <QTcpSocket>

#include <iostream>
using std::istream;
using std::cin;

/*
 *
 * class for save client on server,
 * on client all settigns be kept in @clientsettings@
 * don't use this class, for save clientInfo on client
 *
 */

class ClientInfo {
public:
    ClientInfo();
    ClientInfo(QString str, QTcpSocket* socket, int start_x, int start_y, int id_);
    ~ClientInfo();

    QString getLogin();
    QString getPassword();
    size_t getCurrentEnemyTask(size_t lvl, bool increment);
    size_t getCurrentArrowTask(size_t lvl, bool increment);

    void setSocket(QTcpSocket* socket);

    bool isPlayerPlace(size_t x, size_t y);

    Player* getPlayer();
    size_t getAvatarType();
    const QTcpSocket* getTcpSocket();

private:
    int id;
    size_t avatarType;
    QString login;
    QString password;

    std::unordered_map<size_t, size_t> currentEnemyTask;
    std::unordered_map<size_t, size_t> currentArrowTask;

    QTcpSocket* pTcpSocket;

private:
    Player* player;
public:
    friend std::ostream& operator<< (std::ostream&, const ClientInfo&);
    friend std::istream& operator>> (std::istream&, ClientInfo&);
};

#endif // CLIENTINFO_H
