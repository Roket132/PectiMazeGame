#include "lamp.h"

#include "appsettings.h"

Lamp::Lamp(size_t size) {
    AppSettings &settings = AppSettings::getAppSettings();
    QString stylePrefix = settings.getStyle();

    possibleStandOnObj = true;

    if(size <= 40) {
        def_texture = texture = QPixmap(QStringLiteral(":/%1/src/texture_40/%1/torch_off.png").arg(stylePrefix));
    } else {
        def_texture = texture = QPixmap(QStringLiteral(":/%1/src/texture_80/%1/torch_off.png").arg(stylePrefix));
    }
}


QString Lamp::getTypeObject() {
    return TYPE;
}

void Lamp::update() {

}
