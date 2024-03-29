#include "appsettings.h"

#include <QTemporaryDir>

AppSettings::AppSettings() : stylePrefix("default"), selectedAvatar(1), amountAvatarVariants(4) {}

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

size_t AppSettings::getAmoutnAvatarVariants() {
    return amountAvatarVariants;
}

size_t AppSettings::getAvatar() {
    return selectedAvatar;
}

void AppSettings::setAvatar(size_t type) {
    selectedAvatar = type;
}

std::set<QString> *AppSettings::getPathForEnemyTasks() {
    return &pathForEnemyTasks;
}

std::set<QString> *AppSettings::getPathForArrowTasks() {
    return &pathForArrowTasks;
}
