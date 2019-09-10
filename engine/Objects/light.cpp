#include "light.h"

Light::Light() {

}

Light::Light(QPixmap texture_, std::vector<QPixmap> *frames_) : StateObject (texture_, frames_) {}

QString Light::getTypeObject() {
    return TYPE;
}

void Light::update() {

}
