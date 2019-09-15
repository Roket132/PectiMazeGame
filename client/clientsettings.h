#ifndef CLIENTSETTINGS_H
#define CLIENTSETTINGS_H

#include <experimental/filesystem>
#include <QString>
#include <mutex>

#include "clientinfo.h"
#include "client.h"
#include "maze.h"

/*
 * class for save all client settings on client
 */

namespace fs = std::experimental::filesystem;

class ClientSettings : public QWidget {
Q_OBJECT
public:
    static ClientSettings &getClientSettings();

    void startClient(QString login_, QString password_, bool old = false); // (old == true) if it first start for this client
    void closeClient();

    Client* getClient();

    void createEmptyMaze();
    Maze* getMaze();

private:
    ClientSettings();
    ~ClientSettings();
    ClientSettings& operator=(ClientSettings&) = delete;
    ClientSettings(const ClientSettings&) = delete;
    void clientConnects();

    std::mutex *mutex_;

private slots:
    void slotSetMap(QString);


private:
    Client* client;

    QString login;
    QString password;

    Maze* clientMaze;
};

#endif // CLIENTSETTINGS_H
