#include "wall.h"

Wall::Wall() {

}

Wall::Wall(QPixmap texture_, std::vector<QPixmap> *frames_) : StateObject (texture_, frames_) {}

QString Wall::getTypeObject() {
    return TYPE;
}

void Wall::update() {

}
