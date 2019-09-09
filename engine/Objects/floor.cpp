#include "floor.h"

Floor::Floor() {

}

Floor::Floor(QPixmap texture_, std::vector<QPixmap> *frames_) : StateObject (texture_, frames_) {}

QString Floor::getTypeObject() {
    return TYPE;
}

void Floor::update() {

}
