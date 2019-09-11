#ifndef SERVERSETTINGS_H
#define SERVERSETTINGS_H

#include "maze.h"
#include "server.h"
#include "client/clientinfo.h"
#include "parsing/parsingtools.h"

#include <QWidget>
#include <iostream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

/*
 * Singleton object
 */

/*
 * TODO
 * 1. maze must save clients, not server
 */

class ServerSettings : public QWidget {
Q_OBJECT
public:
    static ServerSettings &getServerSettings(fs::path path = "");

    void startServer();
    void closeServer();

    Maze* createMaze(fs::path);
    Maze* getMaze();

    QString getMapPlayerBySocket(QTcpSocket* socket);
    QString getMapPlayerByPlace(int x, int y, bool extra);

    Player* isPlayer(int x, int y);
    Player* getPlayerBySocket(QTcpSocket* socket);

    /*
     *
     * all settings about rules for action in this metod
     * void doCellAction(Player* player);
     *
     */

    void doCellAction(Player* player); // check are there any actions on cell which player stay and do it;

private:
    ServerSettings(fs::path path);
    ~ServerSettings() {}
    ServerSettings& operator=(ServerSettings&) = delete;
    ServerSettings(const ServerSettings&) = delete;

private:
    Server *server;
    Maze   *maze;
    std::vector<ClientInfo*> clients;

private slots:
    void slotRegNewClient(QString str, QTcpSocket* socket);
    void slotEnterClient(QString str, QTcpSocket* socket);
    void slotMovePlayer(QString str, QTcpSocket* socket);
};

#endif // SERVERSETTINGS_H
