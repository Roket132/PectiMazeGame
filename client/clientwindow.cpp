#include "clientwindow.h"
#include "ui_clientwindow.h"

#include <QThread>
#include <QMessageBox>

ClientWindow::ClientWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWindow)
{
    QCoreApplication::instance()->installEventFilter(this);
    ui->setupUi(this);

    eventWindow = nullptr;

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

        setActions();

        connect(cell, &QPushButton::clicked, [this, cell]() {
            if (actions.count(cell->objectName())) {
                actions[cell->objectName()]();
            }
        });
    }

    thread = new QThread(this);
    eng = new Engine(scenes, invScenes, infoInvScenes);
    eng->moveToThread(thread);
    connect(thread, SIGNAL(started()), eng, SLOT(drawClientMap()));
    thread->start();

    ClientSettings &clientSettings = ClientSettings::getClientSettings();
    connect(&clientSettings, &ClientSettings::signalAttack, this, &ClientWindow::slotAttack);
    connect(&clientSettings, &ClientSettings::signalAnswerSuccessful, this, &ClientWindow::slotAnswerSuccessful);
    connect(&clientSettings, &ClientSettings::signalAnswerIncorrect, this, &ClientWindow::slotAnswerIncorrect);
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

    if (eventWindow) eventWindow->close();

    emit showClientRegWindow();
    event->accept();
}

void ClientWindow::blockMoving() {
    ui->upButton->setEnabled(false);
    ui->rightButton->setEnabled(false);
    ui->downButton->setEnabled(false);
    ui->leftButton->setEnabled(false);
}

void ClientWindow::unlockMoving() {
    ui->upButton->setEnabled(true);
    ui->rightButton->setEnabled(true);
    ui->downButton->setEnabled(true);
    ui->leftButton->setEnabled(true);
}

void ClientWindow::addEventLayout(QPixmap px, std::shared_ptr<Task> task, QString description, std::function<void()> f_btn) {
    if (ui->eventsLayout->count() == 0) {
        QLabel *lb = new QLabel("Для выбора события нажмите на иконку:", this);
        lb->setStyleSheet(QString("font-size: %1px").arg(16));
        ui->eventsLayout->addWidget(lb);
        ui->eventsLayout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    }

    QGridLayout *gl = new QGridLayout(this);
    QPushButton *btn = new QPushButton(this);
    btn->setFixedSize(80, 80);
    btn->setIcon(px);
    btn->setIconSize(btn->size() - QSize(5, 5));
    gl->addWidget(btn, 2, 2);

    connect(btn, &QPushButton::clicked, [=] {
        if (eventWindow) {
            int n = QMessageBox::warning(nullptr,
                                         "Открыть событие",
                                         "Вы хотите отркыть новое событие?\n"
                                         "Старое будет закрыто автоматически!",
                                         "ОК",
                                         "Отмена",
                                         QString(),
                                         0,
                                         1
                                        );
            if (n) {
                return;
            }
        }
        f_btn();
    });

    QLabel *infoLabel = new QLabel(this);
    infoLabel->setText(description);
    gl->addWidget(infoLabel, 2, 3);

    gl->setObjectName(QString::fromStdString(task->getName()));

    eventLayouts.emplace_back(gl);
    ui->eventsLayout->addLayout(gl);
}

void ClientWindow::arrowUsed() {
    ClientSettings &cl = ClientSettings::getClientSettings();
    size_t lvl = 1;
    auto task = cl.getNextArrowTask(lvl);
    if (eventWindow) eventWindow->close();
    eventWindow = new EventWindow(QString::fromStdString(task->getName()), QString::fromStdString(task->getText()), static_cast<size_t>(lvl), "arrow");
    eventWindow->show();

    connect(eventWindow, &EventWindow::closed, [this] {
        eventWindow = nullptr;
    });
}

void ClientWindow::slotAttack(int lvl) {
    blockMoving();

    ClientSettings &cl = ClientSettings::getClientSettings();
    auto task = cl.getNextEnemyTask(static_cast<size_t>(lvl));

    if (task == nullptr) {
        std::cerr << "task == nullptr in slotAttack" << std::endl;
        return;
    }

    addEventLayout(QPixmap(":/res/image/image_80/swords.png"),
                   task,
                "Чтобы продолжить путешествие\n"
                "надо победить врага!",
                [this, task, lvl] {
                     if (eventWindow) eventWindow->close();
                     eventWindow = new EventWindow(QString::fromStdString(task->getName()), QString::fromStdString(task->getText()), static_cast<size_t>(lvl), "enemy");
                     eventWindow->show();

                     connect(eventWindow, &EventWindow::closed, [this] {
                         eventWindow = nullptr;
                     });
                });
}

void ClientWindow::slotAnswerSuccessful(QString mode, QString taskName) {
    eventWindow->close();

    if (mode == "arrow") return;

    int pos = 0;
    for (auto it : eventLayouts) {
        if (it->objectName() == taskName) {
            while (auto *item = it->layout()->takeAt(0)) {
                delete item->widget();
                delete item;
            }
            delete it;
            eventLayouts.erase(eventLayouts.begin() + pos);
        }
        pos++;
    }
    unlockMoving();

    if (eventLayouts.empty()) {
        while (auto *item = ui->eventsLayout->takeAt(0)) {
            delete item->widget();
            delete item;
        }
    }
}

void ClientWindow::slotAnswerIncorrect() {
    QMessageBox::information(nullptr, "Information", "Ответ неверный!");
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
    if (!ui->upButton->isEnabled()) return;

    ClientSettings &clientSetting = ClientSettings::getClientSettings();
    if (clientSetting.getMaze()->isPossibleToGoTo(1, 2)) {
        clientSetting.getClient()->sendToServer("move 1 0;");
    }
}

void ClientWindow::on_rightButton_clicked() {
    if (!ui->rightButton->isEnabled()) return;

    ClientSettings &clientSetting = ClientSettings::getClientSettings();
    if (clientSetting.getMaze()->isPossibleToGoTo(2, 3)) {
        clientSetting.getClient()->sendToServer("move 0 1;");
    }
}

void ClientWindow::on_downButton_clicked() {
    if (!ui->downButton->isEnabled()) return;

    ClientSettings &clientSetting = ClientSettings::getClientSettings();
    if (clientSetting.getMaze()->isPossibleToGoTo(3, 2)) {
        clientSetting.getClient()->sendToServer("move -1 0;");
    }
}

void ClientWindow::on_leftButton_clicked() {
    if (!ui->leftButton->isEnabled()) return;

    ClientSettings &clientSetting = ClientSettings::getClientSettings();
    if (clientSetting.getMaze()->isPossibleToGoTo(2, 1)) {
        clientSetting.getClient()->sendToServer("move 0 -1;");
    }
}

void ClientWindow::setActions() {
    actions["pecti_arrow"] = [this] {
        arrowUsed();
    };
}

bool ClientWindow::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
        if (obj->objectName() == "ClientWindowWindow") {
            QKeyEvent* e = static_cast<QKeyEvent*>(event);
            if (e->isAutoRepeat()) return true;
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

