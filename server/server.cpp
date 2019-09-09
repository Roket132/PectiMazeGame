#include "server.h"
#include "parsing/parsingtools.h"
#include "server/serversettings.h"

#include <iostream>
#include <QtNetwork>
#include <QMessageBox>

Server::Server(int nPort, QWidget* pwgt /*=0*/) : QWidget(pwgt), m_nNextBlockSize(0) {
    m_ptcpServer = new QTcpServer(this);
    if (!m_ptcpServer->listen(QHostAddress::Any, nPort)) {
        QMessageBox::critical(nullptr,
            "Server Error",
            "Unable to start the server:"
            + m_ptcpServer->errorString()
            );
        m_ptcpServer->close();
        return;
    }
    connect(m_ptcpServer, SIGNAL(newConnection()),
            this, SLOT(slotNewConnection()));
}

/*virtual*/ void Server::slotNewConnection()
{
    QTcpSocket* pClientSocket = m_ptcpServer->nextPendingConnection();
    connect(pClientSocket, SIGNAL(disconnected()),
            pClientSocket, SLOT(deleteLater())
           );
    connect(pClientSocket, SIGNAL(readyRead()),
            this,          SLOT(slotReadClient())
           );

    //sendToClient(pClientSocket, "Server Response: Connected!");
}

void Server::slotReadClient()
{
    QTcpSocket* pClientSocket = (QTcpSocket*)sender();
    QDataStream in(pClientSocket);
    in.setVersion(QDataStream::Qt_4_2);
    for (;;) {
        if (!m_nNextBlockSize) {
            if (pClientSocket->bytesAvailable() < sizeof(quint16)) {
                break;
            }
            in >> m_nNextBlockSize;
        }

        if (pClientSocket->bytesAvailable() < m_nNextBlockSize) {
            break;
        }

        QTime   time;
        QString str;
        in >> time >> str;

        std::cerr << "prishlo " << str.toStdString() << std::endl;
        std::vector<QString> requests = pars::splitRequests(str);
        for (auto it : requests) {
            std::vector<QString> req = pars::parseRequest(it);
            if (req[0] == "reg") {
                emit signalRegNewClient(it, pClientSocket);
            } else if (req[0] == "enter") {
                emit signalEnterClient(it, pClientSocket);
            }
        }

        m_nNextBlockSize = 0;
    }

    std::cerr << "ok1" << std::endl;
    ServerSettings &serverSettings = ServerSettings::getServerSettings(/*not first call*/);
    std::cerr << "o21" << std::endl;
    sendToClient(pClientSocket, serverSettings.getMapPlayerBySocket(pClientSocket) + ";");
    std::cerr << "ok3" << std::endl;

}

void Server::sendToClient(QTcpSocket* pSocket, const QString& str)
{
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_2);
    out << quint16(0) << QTime::currentTime() << str;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    pSocket->write(arrBlock);
}
