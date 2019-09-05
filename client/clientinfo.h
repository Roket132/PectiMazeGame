#ifndef CLIENTINFO_H
#define CLIENTINFO_H

#include "parsing/parsingtools.h"

#include <QString>
#include <QTcpSocket>

class ClientInfo
{
public:
    ClientInfo(QString str, QTcpSocket* socket);

    QString getLogin();
    QString getPassword();

    void setSocket(QTcpSocket* socket);

private:
    QString login;
    QString password;

    QTcpSocket* pTcpSocket;
};

#endif // CLIENTINFO_H
