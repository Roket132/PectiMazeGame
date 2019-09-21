#include "clientregwindow.h"
#include "ui_clientregwindow.h"

#include <QCloseEvent>
#include <QRegExpValidator>

#include "appsettings.h"

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
    ui->backEnterButton->hide();

    ui->changeAvatarButton->setText("Изменить\nаватар");

    ui->passwordEdit->setValidator(new QRegExpValidator(QRegExp("^([a-zA-Z0-9!,.@#$%^&*()]+)$")));
    ui->loginEdit->setValidator(new QRegExpValidator(QRegExp("^([a-zA-Z0-9!,.@#$%^&*()]+)$")));
    ui->repeatEdit->setValidator(new QRegExpValidator(QRegExp("^([a-zA-Z0-9!,.@#$%^&*()]+)$")));
}

ClientRegWindow::~ClientRegWindow() {
    delete ui;
}

void ClientRegWindow::closeEvent(QCloseEvent *event) {
    event->accept();
}

void ClientRegWindow::showEvent(QShowEvent *event) {
    AppSettings &settings = AppSettings::getAppSettings();
    ui->avatarLabel->setPixmap(QPixmap(QStringLiteral(":/%1/src/avatars/%1/avatar_%2.jpg").arg(settings.getStyle()).arg(settings.getAvatar())));
    event->accept();
}

void ClientRegWindow::on_regClientButton_clicked() {
    /*
     * show all needed buttons
     */

    ui->avatarLabel->show();
    ui->changeAvatarButton->show();
    ui->repeatLabel->show();
    ui->repeatEdit->show();
    ui->registrationButton->show();
    ui->backEnterButton->show();

    /*
     * clear all edit
     */

    ui->loginEdit->setText("");
    ui->passwordEdit->setText("");
    ui->repeatEdit->setText("");

    /*
     * hide all unneeded btn
     */

    ui->regClientButton->hide();
    ui->startClientButton->hide();
    ui->messageLabel->hide();
}

void ClientRegWindow::registrationConnects(const Client *client) {
    bool c1 = connect(client, SIGNAL(signalSignInFaild()), this, SLOT(slotSignInFaild()));
    bool c2 = connect(client, SIGNAL(signalSignInSuccess()), this, SLOT(slotSignInSuccess()));
     Q_ASSERT(c1); Q_ASSERT(c2);
}

void ClientRegWindow::on_startClientButton_clicked() {
    if (ui->loginEdit->text() == "" || ui->passwordEdit->text() == "") {
        ui->messageLabel->setText("Введите логин и пароль");
        ui->messageLabel->show();
        return;
    }
    ClientSettings &clientSettings = ClientSettings::getClientSettings();
    clientSettings.startClient(ui->loginEdit->text(), ui->passwordEdit->text(), 0, true);
    const Client* client = clientSettings.getClient();
    registrationConnects(client);
}

void ClientRegWindow::on_registrationButton_clicked() {
    if (ui->loginEdit->text() == "") {
        ui->messageLabel->setText("Введите логин");
        ui->messageLabel->show();
        return;
    }
    if (ui->passwordEdit->text() == "") {
        ui->messageLabel->setText("Введите пароль");
        ui->messageLabel->show();
        return;
    }

    ClientSettings &clientSettings = ClientSettings::getClientSettings();
    if (ui->passwordEdit->text() == ui->repeatEdit->text()) {
        AppSettings &settings = AppSettings::getAppSettings();
        clientSettings.startClient(ui->loginEdit->text(), ui->passwordEdit->text(), settings.getAvatar());
        const Client* client = clientSettings.getClient();
        registrationConnects(client);
    } else {
        ui->messageLabel->setText("Пароли не совпадают");
        ui->messageLabel->show();
        return;
    }
    on_backEnterButton_clicked();
}

void ClientRegWindow::slotSignInSuccess() {
    std::cerr << "success" << std::endl;
    clientWindow = new ClientWindow();
    connect(clientWindow, &ClientWindow::showClientRegWindow, this, &ClientRegWindow::show);
    clientWindow->show();
    this->hide();
    ClientSettings &clientSettings = ClientSettings::getClientSettings();
    clientSettings.getClient()->sendToServer("get map");
}

void ClientRegWindow::slotSignInFaild() {
    std::cerr << "faild" << std::endl;
    ui->messageLabel->setText("Неверный логин или пароль");
    ui->messageLabel->show();
}

void ClientRegWindow::on_backButton_clicked() {
    emit showMainWindow();
    this->close();
}



void ClientRegWindow::on_backEnterButton_clicked() {
    //clear all edit
    ui->loginEdit->setText("");
    ui->passwordEdit->setText("");

    // hide

    ui->registrationButton->hide();
    ui->backEnterButton->hide();
    ui->repeatEdit->hide();
    ui->avatarLabel->hide();
    ui->changeAvatarButton->hide();
    ui->messageLabel->hide();
    ui->repeatLabel->hide();

    // show

    ui->regClientButton->show();
    ui->startClientButton->show();
}



void ClientRegWindow::on_changeAvatarButton_clicked() {
    avatarSelectionWindow = new AvatarSelection();
    connect(avatarSelectionWindow, &AvatarSelection::showRegClientWindow, this, &ClientRegWindow::show);
    avatarSelectionWindow->show();
    this->hide();
}
