#include "lamp.h"

Lamp::Lamp() {

}

Lamp::Lamp(QPixmap texture_, std::vector<QPixmap> *frames_) : StateObject (texture_, frames_) {}

QString Lamp::getTypeObject() {
    return TYPE;
}

void Lamp::update() {

}
