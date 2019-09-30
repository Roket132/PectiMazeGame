#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <set>
#include <QString>

class AppSettings
{
public:
    static AppSettings &getAppSettings();

    void setStyle(QString style);
    QString getStyle();

    size_t getAmoutnAvatarVariants();
    size_t getAvatar();
    void setAvatar(size_t type);

    std::set<QString>* getPathForEnemyTasks();
    std::set<QString>* getPathForArrowTasks();

private:
    AppSettings();
    ~AppSettings();
    AppSettings& operator=(AppSettings&) = delete;
    AppSettings(const AppSettings&) = delete;

    QString stylePrefix;
    size_t selectedAvatar;
    size_t amountAvatarVariants;

    std::set<QString> pathForEnemyTasks = {};
    std::set<QString> pathForArrowTasks = {};
};

#endif // APPSETTINGS_H
