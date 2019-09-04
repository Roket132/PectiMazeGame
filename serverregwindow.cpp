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
    QString path = QFileDialog::getExistingDirectory(0, "Choise maze", "");
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

    ServerSettings &serverSettings = ServerSettings::getServerSettings(ui->mazePathEdit->text().toStdString()); // first singleton call
    serverSettings.startServer();
    //Закинуть в конструктр все настройки сервера
    // Сервер не может быть запущени без выбора настроек, think about it
}
