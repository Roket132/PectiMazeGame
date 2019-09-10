#include "lightsource.h"

LightSource::LightSource() {

}

LightSource::LightSource(QPixmap texture_, std::vector<QPixmap> *frames_) : StateObject (texture_, frames_) {}

QString LightSource::getTypeObject() {
    return TYPE;
}

void LightSource::update() {

}
