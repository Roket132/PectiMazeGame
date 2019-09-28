#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <vector>
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

    std::vector<QString>* getPathForEnemyTasks();
    std::vector<QString>* getPathForArrowTasks();

private:
    AppSettings();
    ~AppSettings();
    AppSettings& operator=(AppSettings&) = delete;
    AppSettings(const AppSettings&) = delete;

    QString stylePrefix;
    size_t selectedAvatar;
    size_t amountAvatarVariants;

    std::vector<QString> pathForEnemyTasks = {"C:/Users/Dmitry/Desktop/QtProjects/tasks.txt"};
    std::vector<QString> pathForArrowTasks = {"C:/Users/Dmitry/Desktop/QtProjects/arrowTasks.txt"};
};

#endif // APPSETTINGS_H
