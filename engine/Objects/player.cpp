#include "player.h"

Player::Player() {

}

Player::Player(QPixmap texture_, std::vector<QPixmap> *frames_) : DynamicObject (texture_, frames_) {}

QString Player::getTypeObject() {
    return TYPE;
}


void Player::update() {

}
