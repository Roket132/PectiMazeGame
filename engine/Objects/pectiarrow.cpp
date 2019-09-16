#include "pectiarrow.h"
#include "appsettings.h"

PectiArrow::PectiArrow(size_t size) : StateObject (QPixmap(), nullptr) {
    AppSettings &settings = AppSettings::getAppSettings();
    QString stylePrefix = settings.getStyle();

    if(size <= 40) {
        texture = QPixmap(QStringLiteral(":/%1/src/texture_40/%1/pecti40.png").arg(stylePrefix));
    } else {
        texture = QPixmap(QStringLiteral(":/%1/src/texture_80/%1/Pecti80.png").arg(stylePrefix));
    }
}

QString PectiArrow::getTypeObject() {
    return TYPE;
}

void PectiArrow::update() {

}

