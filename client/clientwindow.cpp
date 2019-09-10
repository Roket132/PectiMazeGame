#include "clientwindow.h"
#include "ui_clientwindow.h"

#include <QThread>

ClientWindow::ClientWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWindow)
{
    ui->setupUi(this);

    int dimensions = 5;
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

    ClientSettings &clientSetting = ClientSettings::getClientSettings();
    clientSetting.createEmptyMaze();

    QThread *thread = new QThread();
    Engine* eng = new Engine(scenes);
    eng->moveToThread(thread);
    //eng->drawClientMap(scenes);
    connect(thread, SIGNAL(started()), eng, SLOT(drawClientMap()));

    thread->start();
    //thread->quit();
}

ClientWindow::~ClientWindow() {
    delete ui;
}

void ClientWindow::closeEvent(QCloseEvent *event) {
    emit showClientRegWindow();
    event->accept();
}

void ClientWindow::on_upButton_clicked() {
    ClientSettings &clientSetting = ClientSettings::getClientSettings();
    clientSetting.getClient()->sendToServer("move 1 0;");
}

void ClientWindow::on_rightButton_clicked() {
    ClientSettings &clientSetting = ClientSettings::getClientSettings();
    clientSetting.getClient()->sendToServer("move 0 1;");
}

void ClientWindow::on_downButton_clicked() {
    ClientSettings &clientSetting = ClientSettings::getClientSettings();
    clientSetting.getClient()->sendToServer("move -1 0;");
}

void ClientWindow::on_leftButton_clicked() {
    ClientSettings &clientSetting = ClientSettings::getClientSettings();
    clientSetting.getClient()->sendToServer("move 0 -1;");
}
