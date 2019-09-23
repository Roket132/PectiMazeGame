#include "player.h"

#include "iostream"
#include "appsettings.h"

Player::Player(size_t size_, QPixmap avatar_) : DynamicObject (), extraVisionTimer(0), extraVision(false), cntPectiArrow(0), fight(false), avatar(avatar_) {
    if (size_ <= 40) {
        texture = def_texture = avatar.scaled(40, 40);
    }
    else {
        texture = def_texture = avatar;
    }
}

Player::Player(QPixmap texture_, std::vector<QPixmap> *frames_) :
    DynamicObject (texture_, frames_), extraVisionTimer(0), extraVision(false), cntPectiArrow(0) {}

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

bool Player::isFight() {
    return fight;
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

void Player::setFight(bool set, size_t enemyDifficulty_) {
    fight = set;
    enemyDifficulty = enemyDifficulty_;
}

void Player::takePectiArrow() {
    cntPectiArrow++;
}

bool Player::usePectiArrow() {
    if (!cntPectiArrow) {
        return false;
    } else {
        cntPectiArrow--;
        return true;
    }
}

int Player::getCntPectiArrow() {
    return cntPectiArrow;
}

int Player::getExtraVisTimer() {
    return extraVisionTimer;
}

size_t Player::getEnemyDifficulty() {
    return enemyDifficulty;
}

bool Player::canMove() {
    return !fight;
}

QPixmap Player::getAvatar() {
    return avatar;
}

void Player::update() {

}
