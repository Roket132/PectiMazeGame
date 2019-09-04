#ifndef CLIENT_H
#define CLIENT_H

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

private slots:
    void slotReadyRead   (                            );
    void slotError       (QAbstractSocket::SocketError);
    void slotSendToServer(                            );
    void slotConnected   (                            );
};

#endif // CLIENT_H
