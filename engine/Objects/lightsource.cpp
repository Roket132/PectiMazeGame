#include "lightsource.h"

LightSource::LightSource() {
    possibleStandOnObj = true;
}

LightSource::LightSource(QPixmap texture_, std::vector<QPixmap> *frames_) : StateObject (texture_, frames_) {
    possibleStandOnObj = true;
}

QString LightSource::getTypeObject() {
    return TYPE;
}

void LightSource::update() {

}
