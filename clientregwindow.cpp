#include "clientregwindow.h"
#include "ui_clientregwindow.h"

#include <QCloseEvent>

ClientRegWindow::ClientRegWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientRegWindow)
{
    ui->setupUi(this);
    ui->messageLabel->hide();
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

void ClientRegWindow::on_regClientButton_clicked()
{
    ClientSettings &clientSettings = ClientSettings::getClientSettings();
    clientSettings.startNewClient(ui->loginEdit->text(), ui->passwordEdit->text());
    const Client* client = clientSettings.getClient();
    bool c1 = connect(client, SIGNAL(signalSignInFaild()), this, SLOT(slotSignInFaild()));
    bool c2 = connect(client, SIGNAL(signalSignInSuccess()), this, SLOT(slotSignInSuccess()));
    Q_ASSERT(c1); Q_ASSERT(c2);

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
    ui->messageLabel->setText("Login or password incorrect");
    ui->messageLabel->show();
}
