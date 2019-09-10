#include "player.h"

#include "iostream"

Player::Player(QPixmap texture_, std::vector<QPixmap> *frames_) : DynamicObject (texture_, frames_), extraVision(false), extraVisionTimer(0) {}

QString Player::getTypeObject() {
    return TYPE;
}

void Player::action() {
    if (extraVisionTimer) {
        (--extraVisionTimer > 0 ? extraVision = true : extraVision = false);
    }
}

bool Player::isExtraVis() {
    return extraVision;
}

bool Player::isExtraLight() {
    return extraLight;
}

void Player::setExtraVision(int time) {
    extraVisionTimer = time;
    extraVision = true;
}

void Player::setExtraLight(bool set) {
    extraLight = set;
}

void Player::update() {

}
