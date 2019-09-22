#include "clientwindow.h"
#include "ui_clientwindow.h"

#include <QThread>

ClientWindow::ClientWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWindow)
{
    QCoreApplication::instance()->installEventFilter(this);
    ui->setupUi(this);


    int dimensions = 5;
    //int cnt = 0;
    for (int i = 0; i < dimensions; i ++) {
        for (int j = 0; j < dimensions; j++) {
            QLabel *cell = new QLabel(this);
            scenes.push_back(cell);
            cell->setFixedSize(80, 80);
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

    for (int i = 0; i < 3; i++) {        
        QVBoxLayout *vbl = new QVBoxLayout(this);
        QPushButton *cell = new QPushButton(this);
        QLabel *infoCell = new QLabel(this);
        cell->setFlat(true);
        cell->setFixedSize(80, 80);
        cell->setIconSize(cell->size());
        infoCell->setFixedSize(80, 20);
        invScenes.push_back(cell);
        infoInvScenes.push_back(infoCell);
        vbl->addWidget(cell);
        vbl->addWidget(infoCell);
        ui->inventoryLayout->addLayout(vbl);

        connect(cell, &QPushButton::pressed, [cell]() {
            ClientSettings &cl = ClientSettings::getClientSettings();
            cl.getClient()->sendToServer(QStringLiteral("inventory %1;").arg(cell->objectName()));
        });
    }

    thread = new QThread(this);
    eng = new Engine(scenes, invScenes, infoInvScenes);
    eng->moveToThread(thread);
    connect(thread, SIGNAL(started()), eng, SLOT(drawClientMap()));
    thread->start();
}

ClientWindow::~ClientWindow() {
    delete eng;
    delete ui;
}

void ClientWindow::closeEvent(QCloseEvent *event) { 
    QCoreApplication::instance()->removeEventFilter(this);

    ClientSettings &cl = ClientSettings::getClientSettings();
    cl.getClient()->sendToServer("Exit");
    cl.closeClient();
    eng->stopEngine();
    thread->quit();

    emit showClientRegWindow();
    event->accept();
}

/*
 * clientMap size == 5,5
 *
 * # 0 1 2 3 4
 * 0 . . . . .
 * 1 . . U . .
 * 2 . L P R .
 * 3 . . D . .
 * 4 . . . . .
 *
 */

void ClientWindow::on_upButton_clicked() {
    ClientSettings &clientSetting = ClientSettings::getClientSettings();
    if (clientSetting.getMaze()->isPossibleToGoTo(1, 2)) {
        clientSetting.getClient()->sendToServer("move 1 0;");
    }
}

void ClientWindow::on_rightButton_clicked() {
    ClientSettings &clientSetting = ClientSettings::getClientSettings();
    if (clientSetting.getMaze()->isPossibleToGoTo(2, 3)) {
        clientSetting.getClient()->sendToServer("move 0 1;");
    }
}

void ClientWindow::on_downButton_clicked() {
    ClientSettings &clientSetting = ClientSettings::getClientSettings();
    if (clientSetting.getMaze()->isPossibleToGoTo(3, 2)) {
        clientSetting.getClient()->sendToServer("move -1 0;");
    }
}

void ClientWindow::on_leftButton_clicked() {
    ClientSettings &clientSetting = ClientSettings::getClientSettings();
    if (clientSetting.getMaze()->isPossibleToGoTo(2, 1)) {
        clientSetting.getClient()->sendToServer("move 0 -1;");
    }
}

bool ClientWindow::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
        if (obj->objectName() == "ClientWindowWindow") {
            QKeyEvent* e = static_cast<QKeyEvent*>(event);
            switch(e->key()) {
            case Qt::Key_Up: ui->rightButton->setFocus(); on_upButton_clicked(); break;
            case Qt::Key_Down: ui->rightButton->setFocus(); on_downButton_clicked(); break;
            case Qt::Key_Left: ui->upButton->setFocus(); on_leftButton_clicked(); break;
            case Qt::Key_Right: ui->upButton->setFocus(); on_rightButton_clicked(); break;
            }
        }
    }
    return QObject::eventFilter(obj, event);
}

