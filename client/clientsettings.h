#ifndef CLIENTSETTINGS_H
#define CLIENTSETTINGS_H

#include <experimental/filesystem>
#include <QString>
#include <mutex>

#include "parsing/taskarchive.h"
#include "clientinfo.h"
#include "client.h"
#include "maze.h"
#include "hud.h"

/*
 * class for save all client settings on client
 */

namespace fs = std::experimental::filesystem;

class ClientSettings : public QWidget {
Q_OBJECT
public:
    static ClientSettings &getClientSettings();

    void startClient(QString login_, QString password_, size_t avatarType, QString ip, bool old = false); // (old == true) if it first start for this client
    void closeClient();

    Client* getClient();
    Maze* getMaze();
    HUD* getHUD();

    void createEmptyMaze();

    std::shared_ptr<Task> getNextEnemyTask(size_t lvl);

    std::shared_ptr<Task> getNextArrowTask(size_t lvl);

private:
    ClientSettings();
    ~ClientSettings();
    ClientSettings& operator=(ClientSettings&) = delete;
    ClientSettings(const ClientSettings&) = delete;
    void clientConnects();

    std::mutex *maze_mutex;
    std::mutex *hud_mutex;

private slots:
    void slotSetMap(QString);
    void slotHUDUpdate(QString);
    void slotSetSettings(QString);
    void slotAction(QString);
    void slotAddTask(QString);

signals:
    void signalAttack(int);
    void signalAnswerSuccessful(QString, QString);
    void signalAnswerIncorrect();

private:
    Client* client;

    QString login;
    QString password;

    TaskArchive archiveEnemyTasks;
    TaskArchive archiveArrowTasks;

    Maze* clientMaze;
    HUD* clientHUD;
};

#endif // CLIENTSETTINGS_H
