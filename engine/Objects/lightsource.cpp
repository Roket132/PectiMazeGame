#include "lightsource.h"

#include "appsettings.h"

LightSource::LightSource(size_t size_) {
    AppSettings &settings = AppSettings::getAppSettings();
    QString stylePrefix = settings.getStyle();

    possibleStandOnObj = true;

    if(size_ <= 40) {
        def_texture = texture = QPixmap(QStringLiteral(":/%1/src/texture_80/%1/bonfire.png").arg(stylePrefix)).scaled(40, 40);
    } else {
        def_texture = texture = QPixmap(QStringLiteral(":/%1/src/texture_80/%1/bonfire.png").arg(stylePrefix));
    }
}


QString LightSource::getTypeObject() {
    return TYPE;
}

void LightSource::update() {

}
