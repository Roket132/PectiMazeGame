#include "client.h"

#include <iostream>
#include <QTime>

Client::Client(const QString& strHost,
                   int            nPort,
                   QWidget*       pwgt /*=0*/
                  ) : QWidget(pwgt)
                    , m_nNextBlockSize(0)
{
    m_pTcpSocket = new QTcpSocket(this);

    m_pTcpSocket->connectToHost(strHost, nPort);
    connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this,         SLOT(slotError(QAbstractSocket::SocketError))
            );
}


void Client::sendToServer(const QString &str)
{
    slotSendToServer(str);
}

void Client::slotReadyRead()
{
    QDataStream in(m_pTcpSocket);
    in.setVersion(QDataStream::Qt_4_2);
    for (;;) {
        if (!m_nNextBlockSize) {
            if (m_pTcpSocket->bytesAvailable() < sizeof(quint16)) {
                break;
            }
            in >> m_nNextBlockSize;
        }

        if (m_pTcpSocket->bytesAvailable() < m_nNextBlockSize) {
            break;
        }

        QTime   time;
        QString str;
        in >> time >> str;

        std::cerr << "Client enter: " << str.toStdString() << std::endl;

        std::vector<QString> requests = pars::splitRequests(str);
        for (auto it : requests) {
            std::vector<QString> req = pars::parseRequest(it);
            if (req[0] == "success") {
                emit signalSignInSuccess();
            } else if (req[0] == "faild") {
                emit signalSignInFaild();
            } else if (req[0] == "regFaild") {
                emit signalRegFaild();
            } else if (req[0] == "map") {
                emit signalSetMap(it);
            } else if (req[0] == "HUD") {
                emit signalHUDUpdate(it);
            } else if (req[0] == "settings") {
                emit signalSetSettings(it);
            } else if (req[0] == "Action") {
                emit signalAction(it);
            } else if (req[0] == "Task") {
                emit signalAddTask(it);
            }
        }

        m_nNextBlockSize = 0;
    }
}


void Client::slotError(QAbstractSocket::SocketError err)
{
    QString strError =
        "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                     "The host was not found." :
                     err == QAbstractSocket::RemoteHostClosedError ?
                     "The remote host is closed." :
                     err == QAbstractSocket::ConnectionRefusedError ?
                     "The connection was refused." :
                     QString(m_pTcpSocket->errorString())
                    );
}

void Client::slotSendToServer(const QString &str)
{
    std::cerr << "Client sended: " << str.toStdString() << std::endl;

    QString send_str = (str.back() == ';' ? str : str + ";");

    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_2);
    out << quint16(0) << QTime::currentTime() << send_str;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    m_pTcpSocket->write(arrBlock);
}

void Client::slotConnected()
{
    //m_ptxtInfo->append("Received the connected() signal");
}
