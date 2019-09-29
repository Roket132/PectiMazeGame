#ifndef INVENTORYACTIONS_H
#define INVENTORYACTIONS_H

#include <QTcpSocket>

#include "maze.h"
#include "server/server.h"
#include "engine/Objects/player.h"

class InventoryActions {
public:
    InventoryActions(Maze* maze, Player* player, QTcpSocket *socket, Server* server);

    void useArrow(std::function<void()> f_send = nullptr);

private:
    Maze* maze_;

    Player* player_;

    QTcpSocket* socket_;

    Server* server_;

    void send(const std::function<void()> &f_send);

    void addPionts(const long long &value);
};

#endif // INVENTORYACTIONS_H
