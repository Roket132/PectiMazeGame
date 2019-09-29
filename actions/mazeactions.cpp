#include "mazeactions.h"

MazeActions::MazeActions(Maze* maze, Player *player, QTcpSocket *socket, Server* server) :
    maze_(maze), player_(player), socket_(socket), server_(server) {}


void MazeActions::takeLamp(std::function<void()> f_send) {
    player_->setExtraLight(true);
    maze_->removeObjectFromCell(player_->getPosition().first, player_->getPosition().second);
    addPoints(1);
    send(f_send);
}

void MazeActions::turnOnLamp(const int &time, std::function<void()> f_send) {
    if (player_->isExtraLight()) {
        player_->setExtraVision(time);
    }
    send(f_send);
}

void MazeActions::takeArrow(std::function<void()> f_send) {
    player_->takePectiArrow();
    maze_->removeObjectFromCell(player_->getPosition().first, player_->getPosition().second);
    send(f_send);
}

void MazeActions::enemyAttack(std::function<void ()> f_send) {
    auto enemy = maze_->enemyAttack(player_->getPosition().first, player_->getPosition().second);
    player_->setFight(true, static_cast<size_t>(enemy.first));
    player_->setCurEnemyPos({enemy.second.first, enemy.second.second});
    send(f_send);
}

void MazeActions::addPoints(const int &value, std::function<void ()> f_send) {
    player_->addScore(value);
}

void MazeActions::winUponEnemy(size_t enemy_lvl, std::function<void ()> f_send) {
    player_->setFight(false, 0);
    auto enemyPos = player_->getCurEnemyPos();
    maze_->killEnemy(enemyPos.first, enemyPos.second);
    addPoints(static_cast<int> (enemy_lvl) * 15);
}


void MazeActions::send(const std::function<void ()> &f_send) {
    if (f_send != nullptr) {
        f_send();
    }
}
