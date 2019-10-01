#include "clientinfo.h"

#include "appsettings.h"

ClientInfo::ClientInfo() {

}

ClientInfo::ClientInfo(QString str, QTcpSocket* socket, int start_x, int start_y, int id_) : id(id_) {
    std::vector<QString> info = pars::parseRequest(str); // if reg then info has only 3(4) parametrs "type login password avatarType"
    login = info[1];
    password = info[2];
    pTcpSocket = socket;
    avatarType = info[3].toUInt();
    AppSettings &settings = AppSettings::getAppSettings();
    player = new Player(40, QPixmap(QStringLiteral(":/%1/src/avatars/%1/avatar_%2.jpg").arg(settings.getStyle()).arg(avatarType)));
    player->moveTo(start_x, start_y);
}

ClientInfo::~ClientInfo() {
    delete pTcpSocket;
    delete player;
}

QString ClientInfo::getLogin()
{
    return login;
}

QString ClientInfo::getPassword()
{
    return password;
}

void ClientInfo::setSocket(QTcpSocket *socket) {
    pTcpSocket = socket;
}

bool ClientInfo::isPlayerPlace(size_t x, size_t y) {
    std::pair<size_t, size_t> pl = player->getPosition();
    return (x == pl.first && y == pl.second);
}

Player* ClientInfo::getPlayer() {
    return player;
}

size_t ClientInfo::getAvatarType() {
    return avatarType;
}

const QTcpSocket *ClientInfo::getTcpSocket()
{
    return pTcpSocket;
}

size_t ClientInfo::getCurrentEnemyTask(size_t lvl, bool inc) {
    if (!currentEnemyTask.count(lvl))
        currentEnemyTask[lvl] = 0;
    if (inc) return currentEnemyTask[lvl]++;
    else
        return currentEnemyTask[lvl];
}

size_t ClientInfo::getCurrentArrowTask(size_t lvl, bool inc) {
    if (!currentArrowTask.count(lvl))
        currentArrowTask[lvl] = 0;
    if (inc) return currentArrowTask[lvl]++;
    else
        return currentArrowTask[lvl];
}

std::ostream &operator<<(std::ostream &out, const ClientInfo &cl) {
    out << cl.id << ' ' << cl.avatarType << ' ' << cl.login.toStdString() << ' '
               << cl.password.toStdString() << std::endl;
    out << cl.currentEnemyTask.size() << std::endl;
    for (auto it : cl.currentEnemyTask) {
        out << it.first << ' ' << it.second << std::endl;
    }
    out << cl.currentArrowTask.size() << std::endl;
    for (auto it : cl.currentArrowTask) {
        out << it.first << ' ' << it.second << std::endl;
    }
    return out << *cl.player;
}

std::istream &operator>>(std::istream &in, ClientInfo &cl) {
    std::string lg, ps;
    in >> cl.id >> cl.avatarType >> lg >> ps;
    cl.login = QString::fromStdString(lg);
    cl.password = QString::fromStdString(ps);

    int m;
    size_t f, s;
    in >> m;
    for (int i = 0; i < m; i++) {
        in >> f >> s;
        cl.currentEnemyTask[f] = s;
    }
    in >> m;
    for (int i = 0; i < m; i++) {
        in >> f >> s;
        cl.currentArrowTask[f] = s;
    }
    AppSettings &settings = AppSettings::getAppSettings();
    cl.player = new Player(40, QPixmap(QStringLiteral(":/%1/src/avatars/%1/avatar_%2.jpg").arg(settings.getStyle()).arg(cl.avatarType)));
    return in >> *cl.player;
}
