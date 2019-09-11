#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serverregwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startServerButton_clicked()
{
    serverRegWindow = new ServerRegWindow(this);
    connect(serverRegWindow, &ServerRegWindow::showMainWindow, this, &MainWindow::show);
    serverRegWindow->setFixedSize(924, 609);
    serverRegWindow->show();
    this->close();
}

void MainWindow::on_startGameButton_clicked()
{
    clientRegWindow = new ClientRegWindow(this);
    connect(clientRegWindow, &ClientRegWindow::showMainWindow, this, &MainWindow::show);
    clientRegWindow->setFixedSize(924, 609);
    clientRegWindow->show();
    this->close();
}
