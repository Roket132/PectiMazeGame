#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QWidget>
#include <QCloseEvent>
#include <QPushButton>
#include <QLabel>
#include <QThread>
#include <vector>

#include "client/clientsettings.h"
#include "engine/engine.h"
#include "client.h"

namespace Ui {
class ClientWindow;
}

class ClientWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ClientWindow(QWidget *parent = nullptr);
    ~ClientWindow() override;

private:
    Ui::ClientWindow *ui;
    //QLabel* scenes[30*30];
    std::vector<QLabel*> scenes;
    std::vector<QPushButton*> invScenes;
    std::vector<QLabel*> infoInvScenes;

    Engine* eng;
    QThread* thread;

    void closeEvent(QCloseEvent *event) override;

    void draw();
    void blockMoving();
    void setEventLayout(QPixmap px);

signals:
    void showClientRegWindow();

private slots:
    void slotAttack(int);
    void on_upButton_clicked();
    void on_rightButton_clicked();
    void on_downButton_clicked();
    void on_leftButton_clicked();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
};

#endif // CLIENTWINDOW_H
