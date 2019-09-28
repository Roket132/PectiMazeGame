#ifndef SERVERSETTINGS_H
#define SERVERSETTINGS_H

#include <QWidget>
#include <iostream>

#include "maze.h"
#include "server.h"
#include "client/clientinfo.h"
#include "parsing/parsingtools.h"
#include "parsing/taskarchive.h"

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

    std::shared_ptr<Task> getNextEnemyTask(QTcpSocket* socket, size_t lvl);
    std::shared_ptr<Task> getNextArrowTask(QTcpSocket* socket, size_t lvl);

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

    void createTasksArchives();

    void sendNextArrowTask(QTcpSocket* socket, size_t lvl = 1);
    void sendNextEnemyTask(QTcpSocket* socket, size_t lvl);

private:
    Server *server;
    Maze   *maze;
    std::vector<ClientInfo*> clients;

    TaskArchive archiveEnemyTasks;
    TaskArchive archiveArrowTasks;

private slots:
    void slotRegNewClient(QString str, QTcpSocket* socket);
    void slotEnterClient(QString str, QTcpSocket* socket);
    void slotMovePlayer(QString str, QTcpSocket* socket);
    void slotUseInventory(QString str, QTcpSocket* socket);
    void slotClientExit(QString str, QTcpSocket* socket);
    void slotCheckAnswer(QString str, QTcpSocket* socket);

signals:
    void signalPlayerConnected(ClientInfo *clInfo);
    void signalPlayerDisconnected(ClientInfo *clInfo);
};

#endif // SERVERSETTINGS_H
