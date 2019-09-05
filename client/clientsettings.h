#ifndef CLIENTSETTINGS_H
#define CLIENTSETTINGS_H

#include "client.h"
#include <QString>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

class ClientSettings : public QWidget {
Q_OBJECT
public:
    static ClientSettings &getClientSettings();

    void startNewClient(QString login_, QString password_);
    void startOldClient(QString login_, QString password_);

    const Client* getClient();

private:
    ClientSettings();
    ~ClientSettings() {}
    ClientSettings& operator=(ClientSettings&) = delete;
    ClientSettings(const ClientSettings&) = delete;

private:
    Client* client;
    QString login;
    QString password;
};

#endif // CLIENTSETTINGS_H
