#include "mainwindow.h"
#include <QApplication>

Q_DECLARE_METATYPE (fs::path);

int main(int argc, char *argv[])
{
    qRegisterMetaType<fs::path>("fs::path");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
