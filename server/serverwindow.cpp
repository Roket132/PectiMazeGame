#include "serverwindow.h"
#include "ui_serverwindow.h"

#include <QThread>

#include "engine/engine.h"

ServerWindow::ServerWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerWindow)
{
    ui->setupUi(this);
    int dimensions = 25;

    //int cnt = 0;
    for (int i = 0; i < dimensions; i ++) {
        for (int j = 0; j < dimensions; j++) {
            QLabel *cell = new QLabel(this);
            scenes.push_back(cell);
            cell->setFixedSize(40, 40);
            cell->setStyleSheet("QLabel { background-color : white; }");
            ui->mapLayout->addWidget(cell, i + 1, j + 1);
        }
    }
    ui->mapLayout->setSpacing(0);
    // Vertical spacers
    ui->mapLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding), 0, 0, 1, dimensions + 2);
    ui->mapLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding), dimensions + 1, 0, 1, dimensions + 2);

    // Horizontal spacers
    ui->mapLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum), 1, 0, dimensions, 1);
    ui->mapLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum), 1, dimensions + 1, dimensions, 1);

    thread = new QThread(this);
    eng = new Engine(scenes);
    eng->moveToThread(thread);
    connect(thread, SIGNAL(started()), eng, SLOT(drawServerMap()));
    thread->start();
}

ServerWindow::~ServerWindow() {
    delete eng;
    delete ui;
}


void ServerWindow::closeEvent(QCloseEvent *event)
{
    eng->stopEngine();
    thread->quit();
    ServerSettings &serverSetting = ServerSettings::getServerSettings();
    serverSetting.closeServer();

    emit showServerRegWindow();
    event->accept();
}
