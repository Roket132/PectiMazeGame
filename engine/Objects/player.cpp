#include "player.h"

#include "iostream"
#include "appsettings.h"

Player::Player(size_t size_, QPixmap avatar_) : DynamicObject (), extraVisionTimer(0), extraVision(false), cntPectiArrow(0),
    fight(false), curEnemyPos({0,0}), score(0), avatar(avatar_) {
    if (size_ <= 40) {
        texture = def_texture = avatar.scaled(40, 40);
    }
    else {
        texture = def_texture = avatar;
    }
}

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

void Player::setAvatarByType(size_t type) {

}

std::pair<size_t, size_t> Player::getCurEnemyPos() const {
    return curEnemyPos;
}

void Player::setCurEnemyPos(const std::pair<size_t, size_t> &value) {
    curEnemyPos = value;
}

void Player::addScore(const long long &add) {
    score += add;
}

long long Player::getScore(){
    return score;
}

bool Player::getExtraVision() const
{
    return extraVision;
}

bool Player::getExtraLight() const
{
    return extraLight;
}

void Player::update() {
    
}

std::istream &operator>>(std::istream &stream, Player &p) {
    return stream >> p.x_ >> p.y_ >>p.extraVisionTimer >> p.extraVision >> p.extraLight
                  >> p.cntPectiArrow >> p.fight >> p.enemyDifficulty
                  >> p.curEnemyPos.first >> p.curEnemyPos.second >> p.score;
}

std::ostream &operator<<(std::ostream &stream, const Player &p) {
    return stream << p.x_ << ' ' << p.y_ << ' ' << p.extraVisionTimer << ' ' << p.extraVision << ' ' << p.extraLight << ' '
                  << p.cntPectiArrow << ' ' << p.fight << ' ' << p.enemyDifficulty << ' '
                  << p.curEnemyPos.first << ' ' << p.curEnemyPos.second << ' ' << p.score;
}
