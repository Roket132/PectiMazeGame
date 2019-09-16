#include "lamp.h"

Lamp::Lamp() {
    possibleStandOnObj = true;
}

Lamp::Lamp(QPixmap texture_, std::vector<QPixmap> *frames_) : StateObject (texture_, frames_) {
    possibleStandOnObj = true;
}

QString Lamp::getTypeObject() {
    return TYPE;
}

void Lamp::update() {

}
