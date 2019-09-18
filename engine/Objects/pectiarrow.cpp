#include "pectiarrow.h"
#include "appsettings.h"

PectiArrow::PectiArrow(size_t size) : StateObject (QPixmap(), nullptr) {
    AppSettings &settings = AppSettings::getAppSettings();
    QString stylePrefix = settings.getStyle();

    possibleStandOnObj = true;

    if(size <= 40) {
        def_texture = texture = QPixmap(QStringLiteral(":/%1/src/texture_80/%1/Pecti.png").arg(stylePrefix)).scaled(40, 40);
    } else {
        def_texture = texture = QPixmap(QStringLiteral(":/%1/src/texture_80/%1/Pecti.png").arg(stylePrefix));
    }
}

QString PectiArrow::getTypeObject() {
    return TYPE;
}

void PectiArrow::update() {

}

