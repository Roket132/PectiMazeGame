#include "pectipatch.h"
#include "appsettings.h"

PectiPatch::PectiPatch(size_t size) : StateObject (QPixmap(), nullptr) {
    AppSettings &settings = AppSettings::getAppSettings();
    QString stylePrefix = settings.getStyle();

    possibleStandOnObj = true;

    if(size <= 40) {
        def_texture = texture = QPixmap(QStringLiteral(":/%1/src/texture_80/%1/PectiPatch.png").arg(stylePrefix)).scaled(40, 40);
    } else {
        def_texture = texture = QPixmap(QStringLiteral(":/%1/src/texture_80/%1/PectiPatch.png").arg(stylePrefix));
    }
}

QString PectiPatch::getTypeObject() {
    return TYPE;
}

void PectiPatch::update() {

}
