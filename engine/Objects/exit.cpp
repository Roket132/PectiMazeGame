#include "exit.h"

#include "appsettings.h"

Exit::Exit(size_t size) : StateObject (QPixmap(), nullptr) {
    AppSettings &settings = AppSettings::getAppSettings();
    QString stylePrefix = settings.getStyle();

    possibleStandOnObj = true;

    if(size <= 40) {
        def_texture = texture = QPixmap(QStringLiteral(":/%1/src/texture_80/%1/exit.jpg").arg(stylePrefix)).scaled(40, 40);
    } else {
        def_texture = texture = QPixmap(QStringLiteral(":/%1/src/texture_80/%1/exit.jpg").arg(stylePrefix));
    }
}

QString Exit::getTypeObject() {
    return TYPE;
}

void Exit::update() {

}
