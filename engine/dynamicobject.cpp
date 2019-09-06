#include "dynamicobject.h"

#include <iostream>

DynamicObject::DynamicObject() {
    std::cerr << "yes" << std::endl;
}

DynamicObject::DynamicObject(QPixmap texture_, std::vector<QPixmap> *frames_) : MazeObject (texture_, frames_), x_(0), y_(0) {}

DynamicObject::~DynamicObject() {

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

std::pair<int, int> DynamicObject::getPlace() {
    return {x_, y_};
}

