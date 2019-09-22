#include "serverwindow.h"
#include "ui_serverwindow.h"

#include <QThread>
#include <QGridLayout>

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

    ServerSettings &serverSettings = ServerSettings::getServerSettings(/*not first call*/);
    connect(&serverSettings, SIGNAL(signalPlayerConnected(ClientInfo*)), this, SLOT(slotPlayerConnected(ClientInfo*)));
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

void ServerWindow::setFocusOnPlayer(Player *player) {
    std::cerr << "set Focus " << player->getPosition().first << std::endl;
}

void ServerWindow::slotPlayerConnected(ClientInfo *clInfo) {
    QGridLayout *lay = new QGridLayout(this);
    QPushButton *avatar = new QPushButton(this);
    QLabel *login = new QLabel(this);
    QLabel *info = new QLabel(this);
    QLabel *points = new QLabel(this);

    Player *player = clInfo->getPlayer();

    avatar->setFixedSize(80, 80);
    login->setFixedSize(80, 80);
    info->setFixedSize(80, 20);
    points->setFixedSize(80, 20);

    avatar->setIcon(player->getAvatar());
    avatar->setIconSize(avatar->size() - QSize(5, 5));
    avatar->setFlat(true);
    connect(avatar, &QPushButton::pressed, [player, this] {
        this->setFocusOnPlayer(player);
    });

    login->setText(QStringLiteral("Игрок: %1").arg(clInfo->getLogin()));
    info->setText("Очки: ");
    points->setText(QStringLiteral("%1").arg(0));

    lay->addWidget(avatar, 1, 1);
    lay->addWidget(login, 1, 2);
    lay->addWidget(info, 2, 1);
    lay->addWidget(points, 2, 2);
    ui->playerCellsLayout->addLayout(lay);
}
