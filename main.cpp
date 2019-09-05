#include "mainwindow.h"
#include <QApplication>

Q_DECLARE_METATYPE (fs::path);
Q_DECLARE_METATYPE (QString);
Q_DECLARE_METATYPE (QTcpSocket*);


int main(int argc, char *argv[])
{
    qRegisterMetaType<fs::path>("fs::path");
    qRegisterMetaType<QString>("QString");
    qRegisterMetaType<QTcpSocket*>("QTcpSocket*");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
