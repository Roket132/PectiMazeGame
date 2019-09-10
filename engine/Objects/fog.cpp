#include "fog.h"

Fog::Fog() {

}

Fog::Fog(QPixmap texture_, std::vector<QPixmap> *frames_) : StateObject (texture_, frames_) {}

QString Fog::getTypeObject() {
    return TYPE;
}

void Fog::update() {

}
