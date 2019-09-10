#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QCloseEvent>
#include <vector>

#include "engine/Objects/player.h"
#include "serversettings.h"

namespace Ui {
class ServerWindow;
}

class ServerWindow : public QWidget {
    Q_OBJECT

public:
    explicit ServerWindow(QWidget *parent = nullptr);
    ~ServerWindow() override;

private:
    Ui::ServerWindow *ui;
    //QLabel* scenes[30*30];
    std::vector<QLabel*> scenes;


     void closeEvent(QCloseEvent *event) override;

signals:
    void showServerRegWindow();

};

#endif // SERVERWINDOW_H
