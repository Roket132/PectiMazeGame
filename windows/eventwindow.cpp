#include "eventwindow.h"
#include "ui_eventwindow.h"

EventWindow::EventWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EventWindow)
{
    ui->setupUi(this);
}

EventWindow::~EventWindow()
{
    delete ui;
}
