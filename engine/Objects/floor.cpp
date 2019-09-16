#include "floor.h"

#include "appsettings.h"

Floor::Floor(size_t size) : StateObject (QPixmap(), nullptr) {
    AppSettings &settings = AppSettings::getAppSettings();
    QString stylePrefix = settings.getStyle();

    possibleStandOnObj = true;

    if(size <= 40) {
        texture = QPixmap(QStringLiteral(":/%1/src/texture_40/%1/floor.jpg").arg(stylePrefix));
    } else {
        texture = QPixmap(QStringLiteral(":/%1/src/texture_80/%1/floor.jpg").arg(stylePrefix));
    }
}

QString Floor::getTypeObject() {
    return TYPE;
}

void Floor::update() {

}
