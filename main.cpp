#include "mainwindow.h"
#include <QApplication>

Q_DECLARE_METATYPE (fs::path);
Q_DECLARE_METATYPE (QString);
Q_DECLARE_METATYPE (QTcpSocket*);
Q_DECLARE_METATYPE (Player*);
Q_DECLARE_METATYPE (ClientInfo*);

#include "parsing/taskarchive.h"


int main(int argc, char *argv[])
{
    qRegisterMetaType<fs::path>("fs::path");
    qRegisterMetaType<QString>("QString");
    qRegisterMetaType<QTcpSocket*>("QTcpSocket*");
    qRegisterMetaType<Player*>("Player*");
    qRegisterMetaType<Player*>("ClientInfo*");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
