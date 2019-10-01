#include "serverwindow.h"
#include "ui_serverwindow.h"

#include <fstream>
#include <QThread>
#include <QGridLayout>

#include "engine/engine.h"

ServerWindow::ServerWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerWindow)
{
    ui->setupUi(this);

    dimensions = 25;
    focusX = static_cast<size_t>(dimensions / 2);
    focusY = static_cast<size_t>(dimensions / 2);
    shiftNegative = dimensions / 2 - 1;
    shiftPositive = dimensions / 2 + dimensions % 2 + 1;
    focusPlayer = nullptr;

    //int cnt = 0;
    for (size_t i = 0; i < dimensions; i ++) {
        for (size_t j = 0; j < dimensions; j++) {
            QLabel *cell = new QLabel(this);
            scenes.push_back(cell);
            cell->setFixedSize(40, 40);
            cell->setStyleSheet("QLabel { background-color : white; }");
            ui->mapLayout->addWidget(cell, static_cast<int>(i + 1), static_cast<int>(j + 1));
        }
    }
    ui->mapLayout->setSpacing(0);
    // Vertical spacers
    int dim = static_cast<int>(dimensions);
    ui->mapLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding), 0, 0, 1, dim + 2);
    ui->mapLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding), dim + 1, 0, 1, dim + 2);

    // Horizontal spacers
    ui->mapLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum), 1, 0, dim, 1);
    ui->mapLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum), 1, dim + 1, dim, 1);

    thread = new QThread(this);
    eng = new Engine(scenes, this);
    eng->moveToThread(thread);
    connect(thread, SIGNAL(started()), eng, SLOT(drawServerMap()));
    thread->start();

    ServerSettings &serverSettings = ServerSettings::getServerSettings(/*not first call*/);
    connect(&serverSettings, SIGNAL(signalPlayerConnected(ClientInfo*)), this, SLOT(slotPlayerConnected(ClientInfo*)));
    connect(&serverSettings, SIGNAL(signalPlayerDisconnected(ClientInfo*)), this, SLOT(slotPlayerDisconnected(ClientInfo*)));
    connect(&serverSettings, &ServerSettings::signalAutoFocus, this, &ServerWindow::autoFocus);
}

ServerWindow::~ServerWindow() {
    delete eng;
    delete ui;
}

size_t ServerWindow::getFocusX() const
{
    return focusX;
}

size_t ServerWindow::getFocusY() const
{
    return focusY;
}

size_t ServerWindow::getShiftNegative() const
{
    return shiftNegative;
}

size_t ServerWindow::getShiftPositive() const
{
    return shiftPositive;
}

size_t ServerWindow::getDimensions() const
{
    return dimensions;
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
    focusPlayer = player;
    ServerSettings &serverSettings = ServerSettings::getServerSettings(/*not first call*/);
    focusX = std::max(shiftNegative, player->getPosition().first);
    focusX = std::min(focusX, serverSettings.getMaze()->height() - shiftPositive - 1);
    focusY = std::max(shiftNegative, player->getPosition().second);
    focusY = std::min(focusY, serverSettings.getMaze()->width() - shiftPositive - 1);
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
    lay->setObjectName(clInfo->getLogin());
    ui->playerCellsLayout->addLayout(lay);
    playerLayouts.push_back(lay);
}

void ServerWindow::slotPlayerDisconnected(ClientInfo *clInfo) {
    int pos = 0;
    for (auto it : playerLayouts) {
        if (it->objectName() == clInfo->getLogin()) {
            while (auto *item = it->layout()->takeAt(0)) {
                delete item->widget();
                delete item;
            }
            delete it;
            playerLayouts.erase(playerLayouts.begin() + pos);
            return;
        }
        pos++;
    }
}

void ServerWindow::autoFocus() {
    std::cerr << "ok " << std::endl;
    if (focusPlayer != nullptr) {
        std::cerr << "nullptr " << std::endl;
        auto fx = focusPlayer->getPosition().first;
        auto fy = focusPlayer->getPosition().second;
        if (fx + 3 > focusX + shiftPositive ||
                fx - 2 < focusX - shiftNegative ||
                fy + 3 > focusY + shiftPositive ||
                fy - 2 < focusY - shiftNegative) {
            setFocusOnPlayer(focusPlayer);
        }
    }
}

void ServerWindow::on_saveButton_clicked() {
    ServerSettings &serverSetting = ServerSettings::getServerSettings();
    std::fstream out;
    try {
        out.open("C:/Users/Dmitry/Desktop/QtProjects/serverSave.txt", std::ifstream::out);
    } catch (std::ifstream::failure e) {
        std::cerr << "cannot save server" << std::endl;
        return;;
    }

    out << *serverSetting.getMaze() << std::endl;
    out << serverSetting.getClients().size() << std::endl;
    for (auto cl : serverSetting.getClients()) {
        out << *cl << std::endl;
    }
    std::cerr << "save successful" << std::endl;
}
