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
    static ServerSettings &getServerSettings();

    void startServer(fs::path path);
    void closeServer();

    Maze* createMaze(fs::path);
    Maze* getMaze();

    QString getMapPlayerBySocket(QTcpSocket* socket);
    QString getMapPlayerByPlace(int x, int y, bool extra);

    Player* isPlayer(int x, int y);
    Player* getPlayerBySocket(QTcpSocket* socket);
    ClientInfo* getClientInfoBySocket(QTcpSocket* socket);

    /*
     *
     * all settings about rules for action in this metod
     * void doCellAction(Player* player);
     *
     */

    void doCellAction(Player* player, QTcpSocket *socket); // check are there any actions on cell which player stay and do it;

private:
    ServerSettings();
    ~ServerSettings();
    ServerSettings& operator=(ServerSettings&) = delete;
    ServerSettings(const ServerSettings&) = delete;

    void sendSettingsToClient(QTcpSocket *socket);

private:
    Server *server;
    Maze   *maze;
    std::vector<ClientInfo*> clients;

private slots:
    void slotRegNewClient(QString str, QTcpSocket* socket);
    void slotEnterClient(QString str, QTcpSocket* socket);
    void slotMovePlayer(QString str, QTcpSocket* socket);
    void slotUseInventory(QString str, QTcpSocket* socket);

signals:
    void signalPlayerConnected(ClientInfo *clInfo);
};

#endif // SERVERSETTINGS_H
