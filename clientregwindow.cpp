#include "clientregwindow.h"
#include "ui_clientregwindow.h"

#include <QCloseEvent>

ClientRegWindow::ClientRegWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientRegWindow)
{
    ui->setupUi(this);
    ui->avatarLabel->hide();
    ui->changeAvatarButton->hide();
    ui->repeatLabel->hide();
    ui->repeatEdit->hide();
    ui->registrationButton->hide();
    ui->messageLabel->hide();

    ui->changeAvatarButton->setText("Изменить\nаватар");
    ui->avatarLabel->setPixmap(QPixmap(":/res/image/image_80/man_1.jpg"));
}

ClientRegWindow::~ClientRegWindow()
{
    delete ui;
}

void ClientRegWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
}

void ClientRegWindow::on_regClientButton_clicked()
{
    ui->avatarLabel->show();
    ui->changeAvatarButton->show();
    ui->repeatLabel->show();
    ui->repeatEdit->show();
    ui->registrationButton->show();

    ui->regClientButton->hide();
    ui->startClientButton->hide();
    ui->messageLabel->hide();
}

void ClientRegWindow::on_startClientButton_clicked()
{   
    ClientSettings &clientSettings = ClientSettings::getClientSettings();
    clientSettings.startOldClient(ui->loginEdit->text(), ui->passwordEdit->text());
    const Client* client = clientSettings.getClient();
    bool c1 = connect(client, SIGNAL(signalSignInFaild()), this, SLOT(slotSignInFaild()));
    bool c2 = connect(client, SIGNAL(signalSignInSuccess()), this, SLOT(slotSignInSuccess()));
    Q_ASSERT(c1); Q_ASSERT(c2);
}

void ClientRegWindow::on_registrationButton_clicked()
{
    if (ui->loginEdit->text() == "") {
        ui->messageLabel->setText("Введите логин");
        ui->messageLabel->show();
    }
    if (ui->passwordEdit->text() == "") {
        ui->messageLabel->setText("Введите пароль");
        ui->messageLabel->show();
    }

    ClientSettings &clientSettings = ClientSettings::getClientSettings();
    if (ui->passwordEdit->text() == ui->repeatEdit->text()) {
        clientSettings.startNewClient(ui->loginEdit->text(), ui->passwordEdit->text());
        const Client* client = clientSettings.getClient();
        bool c1 = connect(client, SIGNAL(signalSignInFaild()), this, SLOT(slotSignInFaild()));
        bool c2 = connect(client, SIGNAL(signalSignInSuccess()), this, SLOT(slotSignInSuccess()));
        Q_ASSERT(c1); Q_ASSERT(c2);
    } else {
        ui->messageLabel->setText("Пароли не совпадают");
        ui->messageLabel->show();
    }
}

void ClientRegWindow::slotSignInSuccess()
{
    std::cerr << "success" << std::endl;
    clientWindow = new ClientWindow();
    connect(clientWindow, &ClientWindow::showClientRegWindow, this, &ClientRegWindow::show);
    clientWindow->show();
    this->hide();
}

void ClientRegWindow::slotSignInFaild()
{
    std::cerr << "faild" << std::endl;
    ui->messageLabel->setText("Неверный логин или пароль");
    ui->messageLabel->show();
}

void ClientRegWindow::on_backButton_clicked()
{
    emit showMainWindow();
    this->close();
}


