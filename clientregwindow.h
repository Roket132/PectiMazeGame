#ifndef CLIENTREGWINDOW_H
#define CLIENTREGWINDOW_H

#include "client/clientsettings.h"
#include "client/clientwindow.h"

#include <iostream>
#include <QWidget>

namespace Ui {
class ClientRegWindow;
}

class ClientRegWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ClientRegWindow(QWidget *parent = nullptr);
    ~ClientRegWindow();

private:
    Ui::ClientRegWindow *ui;
    ClientWindow* clientWindow;

    void closeEvent(QCloseEvent *event) override;

signals:
    void showMainWindow();
private slots:
    void on_regClientButton_clicked();
    void on_startClientButton_clicked();

    void slotSignInSuccess();
    void slotSignInFaild();
    void on_backButton_clicked();
    void on_registrationButton_clicked();
    void on_backEnterButton_clicked();
};

#endif // CLIENTREGWINDOW_H
