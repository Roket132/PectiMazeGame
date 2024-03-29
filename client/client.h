#ifndef CLIENT_H
#define CLIENT_H

#include "parsing/parsingtools.h"

#include <QWidget>
#include <QTcpSocket>

class QTextEdit;
class QLineEdit;

class Client : public QWidget {
Q_OBJECT
private:
    QTcpSocket* m_pTcpSocket;
    quint16     m_nNextBlockSize;

public:
    Client(const QString& strHost, int nPort, QWidget* pwgt = nullptr);

    void sendToServer(const QString &str);

private slots:
    void slotReadyRead   (                            );
    void slotError       (QAbstractSocket::SocketError);
    void slotSendToServer(const QString &str          );
    void slotConnected   (                            );

signals:
    void signalRegFaild();
    void signalSignInFaild();
    void signalSignInSuccess();
    void signalSetMap(QString);
    void signalHUDUpdate(QString);
    void signalSetSettings(QString);
    void signalAction(QString);
    void signalAddTask(QString);
};

#endif // CLIENT_H
