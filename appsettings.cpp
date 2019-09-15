#include "appsettings.h"

AppSettings::AppSettings() : stylePrefix("default") {}

AppSettings::~AppSettings() {}

AppSettings &AppSettings::getAppSettings() {
    static AppSettings inst;
    return inst;
}

void AppSettings::setStyle(QString style) {
    stylePrefix = style;
}

QString AppSettings::getStyle() {
    return stylePrefix;
}


