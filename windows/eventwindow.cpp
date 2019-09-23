#include "eventwindow.h"
#include "ui_eventwindow.h"

#include <QMessageBox>

EventWindow::EventWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EventWindow)
{
    ui->setupUi(this);
    emit opened();
}

EventWindow::~EventWindow()
{
    delete ui;
}

void EventWindow::closeEvent(QCloseEvent *event) {
/*
    int n = QMessageBox::warning(nullptr,
                                 "Выйти",
                                 "Вы действительно хотите закрыть окно события?",
                                 "ОК",
                                 "Отмена",
                                 QString(),
                                 0,
                                 1
                                );
    if (n) {
        event->ignore();
        return;
    }
*/
    emit closed();
    event->accept();
}
