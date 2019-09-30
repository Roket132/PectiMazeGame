#include "serverregwindow.h"
#include "ui_serverregwindow.h"
#include "server/serversettings.h"

#include <iostream>
#include <QCloseEvent>
#include <QFileDialog>
#include <QListWidgetItem>

#include "appsettings.h"

ServerRegWindow::ServerRegWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerRegWindow)
{    
    ui->setupUi(this);
    ui->unvisableBtn->hide();

    //ui->commonSettingsTab->setf
    ui->toolBox->setCurrentIndex(0);
    ui->tabWidget->setCurrentIndex(0);


    AppSettings &appSettings = AppSettings::getAppSettings();

    enemyPaths = appSettings.getPathForEnemyTasks();
    arrowPaths = appSettings.getPathForArrowTasks();

    for (auto it : *appSettings.getPathForEnemyTasks()) {
        ui->enemyTasksList->addItem(it);
    }

    for (auto it : *appSettings.getPathForArrowTasks()) {
        ui->arrowTasksList->addItem(it);
    }

    ui->enemyTasksList->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->arrowTasksList->setSelectionMode(QAbstractItemView::ExtendedSelection);
}

ServerRegWindow::~ServerRegWindow()
{
    delete ui;
}

void ServerRegWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
}

void ServerRegWindow::on_choiseMazeButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(0, "Choise maze", "", "*.txt");
    ui->mazePathEdit->setText(path);
}

void ServerRegWindow::on_startServerButton_clicked()
{
    fs::path mazePath(ui->mazePathEdit->text().toStdString());
    try {
        if (fs::is_empty(mazePath) || fs::is_block_file(mazePath)) {
            return;
        }
    } catch (fs::filesystem_error e) {
        std::cerr << e.what() << std::endl;
    }

    ServerSettings &serverSettings = ServerSettings::getServerSettings(); // first singleton call
    serverSettings.startServer(ui->mazePathEdit->text().toStdString());

    serverWindow = new ServerWindow();
    connect(serverWindow, &ServerWindow::showServerRegWindow, this, &ServerRegWindow::show);
    serverWindow->show();
    this->hide();

    //Закинуть в конструктр все настройки сервера
    // Сервер не может быть запущени без выбора настроек, think about it
}

void ServerRegWindow::on_backButton_clicked()
{
    emit showMainWindow();
    this->close();
}

void ServerRegWindow::on_addFileButton_clicked() {
    auto files = QFileDialog::getOpenFileNames(nullptr, "Выбор задач для боёв", "", "*.txt");
    for (auto it : files) {
        if (!enemyPaths->count(it)) {
            enemyPaths->insert(it);
            ui->enemyTasksList->addItem(it);
        }
    }
}

void ServerRegWindow::on_deleteFileButton_clicked() {
    auto items = ui->enemyTasksList->selectedItems();
    for (auto it : items) {
        auto name = it->text();
        enemyPaths->erase(name);
        delete it;
    }
}

void ServerRegWindow::on_addFileButton_2_clicked() {
    auto files = QFileDialog::getOpenFileNames(nullptr, "Выбор задач для стрелок", "", "*.txt");
    for (auto it : files) {
        if (!arrowPaths->count(it)) {
            arrowPaths->insert(it);
            ui->arrowTasksList->addItem(it);
        }
    }
}

void ServerRegWindow::on_deleteFileButton_2_clicked() {
    auto items = ui->arrowTasksList->selectedItems();
    for (auto it : items) {
        auto name = it->text();
        arrowPaths->erase(name);
        delete it;
    }
}
