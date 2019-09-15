#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QString>

class AppSettings
{
public:
    static AppSettings &getAppSettings();

    void setStyle(QString style);
    QString getStyle();

private:
    AppSettings();
    ~AppSettings();
    AppSettings& operator=(AppSettings&) = delete;
    AppSettings(const AppSettings&) = delete;

    QString stylePrefix;
};

#endif // APPSETTINGS_H
