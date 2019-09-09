#ifndef CLIENTSETTINGS_H
#define CLIENTSETTINGS_H

#include <experimental/filesystem>
#include <QString>

#include "client.h"
#include "maze.h"



namespace fs = std::experimental::filesystem;

class ClientSettings : public QWidget {
Q_OBJECT
public:
    static ClientSettings &getClientSettings();

    void startNewClient(QString login_, QString password_);
    void startOldClient(QString login_, QString password_);

    const Client* getClient();

    void createEmptyMaze();
    Maze* getMaze();

private:
    ClientSettings();
    ~ClientSettings() {}
    ClientSettings& operator=(ClientSettings&) = delete;
    ClientSettings(const ClientSettings&) = delete;
    void clientConnects();

private slots:
    void slotSetMap(QString);


private:
    Client* client;
    QString login;
    QString password;
    Maze* clientMaze;
};

#endif // CLIENTSETTINGS_H
