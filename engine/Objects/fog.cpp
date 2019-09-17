#include "fog.h"

#include "appsettings.h"

Fog::Fog(size_t size): size_(size) {
    AppSettings &settings = AppSettings::getAppSettings();
    QString stylePrefix = settings.getStyle();

    possibleStandOnObj = true;
    makeShape("up", 1);

    if(size_ <= 40) {
        def_texture = QPixmap(QStringLiteral(":/%1/src/texture_40/%1/fog_up_v1.jpg").arg(stylePrefix));
    } else {
        def_texture = QPixmap(QStringLiteral(":/%1/src/texture_80/%1/fog_up_v1.jpg").arg(stylePrefix));
    }
}

QString Fog::getTypeObject() {
    return TYPE;
}

void Fog::makeShape(QString type, int number) {
    AppSettings &settings = AppSettings::getAppSettings();
    QString stylePrefix = settings.getStyle();

    if(size_ <= 40) {
        texture = QPixmap(QStringLiteral(":/%1/src/texture_40/%1/fog_up_v%2.jpg").arg(stylePrefix).arg(number));
    } else {
        texture = QPixmap(QStringLiteral(":/%1/src/texture_80/%1/fog_up_v%2.jpg").arg(stylePrefix).arg(number));
    }

    QMatrix mt90, mt180, mt270;
    mt90.rotate(90);
    mt180.rotate(180);
    mt270.rotate(270);

    if (type == "right") {
        texture = texture.transformed(mt90);
    } else if (type == "down") {
        texture = texture.transformed(mt180);
    } else if (type == "left") {
        texture = texture.transformed(mt270);
    }
}

void Fog::update() {

}
