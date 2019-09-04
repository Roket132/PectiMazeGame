#include "clientregwindow.h"
#include "ui_clientregwindow.h"

#include <QCloseEvent>

ClientRegWindow::ClientRegWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientRegWindow)
{
    ui->setupUi(this);
}

ClientRegWindow::~ClientRegWindow()
{
    delete ui;
}

void ClientRegWindow::closeEvent(QCloseEvent *event)
{
    emit showMainWindow();
    event->accept();
}
