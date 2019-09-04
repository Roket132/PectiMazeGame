#include "player.h"

Player::Player(QPixmap texture_, std::vector<QPixmap> *frames_)
{
    texture = texture_;
    frames.clear();
    for (auto it : *frames_) {
        frames.push_back(it);
    }
}

Player::~Player()
{

}

void Player::update()
{

}
