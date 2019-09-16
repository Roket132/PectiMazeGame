#include "pectipatch.h"
#include "appsettings.h"

PectiPatch::PectiPatch(size_t size) : StateObject (QPixmap(), nullptr) {
    AppSettings &settings = AppSettings::getAppSettings();
    QString stylePrefix = settings.getStyle();

    possibleStandOnObj = true;

    if(size <= 40) {
        texture = QPixmap(QStringLiteral(":/%1/src/texture_40/%1/PectPatch40.png").arg(stylePrefix));
    } else {
        texture = QPixmap(QStringLiteral(":/%1/src/texture_80/%1/PectiPatch80.png").arg(stylePrefix));
    }
}

QString PectiPatch::getTypeObject() {
    return TYPE;
}

void PectiPatch::update() {

}
