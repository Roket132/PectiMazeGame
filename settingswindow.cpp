#include "settingswindow.h"
#include "ui_settingswindow.h"

#include <QCloseEvent>
#include <iostream>
#include "appsettings.h"

SettingsWindow::SettingsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

void SettingsWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
}

void SettingsWindow::on_backBtn_clicked()
{
    emit showMainWindow();
    this->close();
}

void SettingsWindow::on_okButton_clicked() {
    AppSettings &settings = AppSettings::getAppSettings();
    settings.setStyle(ui->styleBox->currentText().toLower());



    std::cerr << settings.getStyle().toStdString() << std::endl;

    on_backBtn_clicked();
}
