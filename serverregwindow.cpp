#include "serverregwindow.h"
#include "ui_serverregwindow.h"
#include "server/serversettings.h"

#include <iostream>
#include <QCloseEvent>
#include <QFileDialog>



ServerRegWindow::ServerRegWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerRegWindow)
{    
    ui->setupUi(this);
}

ServerRegWindow::~ServerRegWindow()
{
    delete ui;
}

void ServerRegWindow::closeEvent(QCloseEvent *event)
{
    emit showMainWindow();
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

    std::cerr << "servRegWin: " << ui->mazePathEdit->text().toStdString() << std::endl;

    ServerSettings &serverSettings = ServerSettings::getServerSettings(ui->mazePathEdit->text().toStdString()); // first singleton call
    std::cerr << "servRegWin: " << ui->mazePathEdit->text().toStdString() << std::endl;
    serverSettings.startServer();

    serverWindow = new ServerWindow();
    connect(serverWindow, &ServerWindow::showServerRegWindow, this, &ServerRegWindow::show);
    serverWindow->show();
    this->hide();

    //Закинуть в конструктр все настройки сервера
    // Сервер не может быть запущени без выбора настроек, think about it
}
