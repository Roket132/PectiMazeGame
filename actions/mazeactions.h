#ifndef MAZEACTIONS_H
#define MAZEACTIONS_H

#include <QString>
#include <QTcpSocket>
#include <functional>

#include "engine/Objects/player.h"
#include "server/server.h"
#include "maze.h"

class MazeActions {
public:
    MazeActions(Maze* maze, Player* player, QTcpSocket *socket, Server* server);

    void takeLamp(std::function<void()> f_send = nullptr);

    void turnOnLamp(const int &time, std::function<void()> f_send = nullptr);

    void takeArrow(std::function<void()> f_send = nullptr);

    void enemyAttack(std::function<void()> f_send = nullptr);

    void addPoints(const long long &value, std::function<void()> f_send = nullptr);

    void winUponEnemy(size_t enemyLvl, std::function<void()> f_send = nullptr);

private:
    Maze* maze_;

    Player* player_;

    QTcpSocket* socket_;

    Server* server_;

    void send(const std::function<void()> &f_send);
};

#endif // MAZEACTIONS_H
