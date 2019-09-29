#include "inventoryactions.h"

InventoryActions::InventoryActions(Maze *maze, Player *player, QTcpSocket *socket, Server *server) :
    maze_(maze), player_(player), socket_(socket), server_(server) {}

void InventoryActions::useArrow(std::function<void ()> f_send) {
    if (player_->usePectiArrow()) {
        maze_->setPectiArrow(player_->getPosition().first, player_->getPosition().second);
        addPionts(10);
        send(f_send);
    }
}

void InventoryActions::send(const std::function<void ()> &f_send) {
    if (f_send != nullptr) {
        f_send();
    }
}

void InventoryActions::addPionts(const long long &value) {
    player_->addScore(value);
}
