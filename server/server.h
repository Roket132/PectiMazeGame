#ifndef SERVER_H
#define SERVER_H

#include <QWidget>

class QTcpServer;
class QTextEdit;
class QTcpSocket;

class Server : public QWidget {
Q_OBJECT
private:
    QTcpServer* m_ptcpServer;
    QTextEdit*  m_ptxt;
    quint16     m_nNextBlockSize;

private:
    void sendToClient(QTcpSocket* pSocket, const QString& str);

public:
    Server(int nPort, QWidget* pwgt = nullptr);

public slots:
    virtual void slotNewConnection();
            void slotReadClient   ();
};

#endif // SERVER_H
