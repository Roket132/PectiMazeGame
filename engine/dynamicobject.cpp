#include "dynamicobject.h"

DynamicObject::DynamicObject() {

}

DynamicObject::DynamicObject(QPixmap texture_, std::vector<QPixmap> *frames_) : MazeObject (texture_, frames_), x_(0), y_(0) {}

DynamicObject::~DynamicObject() {

}

void DynamicObject::move(int dx, int dy) {
    if (dx > 0 && !dy) moveUp();
    else if (dx < 0 && !dy) moveDown();
    else if (!dx && dy > 0) moveRight();
    else if (!dx && dy < 0) moveLeft();
}

void DynamicObject::moveTo(int x, int y) {
    x_ = x;
    y_ = y;
}

void DynamicObject::moveRight() {
    moveTo(x_, y_ + 1);
}

void DynamicObject::moveLeft() {
    moveTo(x_, y_ - 1);
}

void DynamicObject::moveDown() {
    moveTo(x_ + 1, y_);
}

void DynamicObject::moveUp() {
    moveTo(x_ - 1, y_);
}

std::pair<size_t, size_t> DynamicObject::getPosition() {
    return {x_, y_};
}

