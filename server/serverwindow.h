#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QCloseEvent>
#include <QGridLayout>
#include <vector>

#include "engine/engine.h"
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

    size_t getFocusX() const;

    size_t getFocusY() const;

    size_t getShiftNegative() const;

    size_t getShiftPositive() const;

    size_t getDimensions() const;

    std::vector<QGridLayout *> getPlayerLayouts() const;

    std::vector<std::pair<QString, QLabel *> > getPointLayouts() const;

private:
    Ui::ServerWindow *ui;
    //QLabel* scenes[30*30];
    std::vector<QLabel*> scenes;

    Engine* eng;
    QThread* thread;
    std::vector<QGridLayout*> playerLayouts;
    std::vector<std::pair<QString, QLabel*>> pointLayouts;

    size_t dimensions, shiftNegative, shiftPositive;
    size_t focusX, focusY;
    Player* focusPlayer;

     void closeEvent(QCloseEvent *event) override;

     void setFocusOnPlayer(Player* player);

private slots:
     void slotPlayerConnected(ClientInfo *clInfo);
     void slotPlayerDisconnected(ClientInfo *clInfo);
     void autoFocus();

     void on_saveButton_clicked();

signals:
    void showServerRegWindow();

};

#endif // SERVERWINDOW_H
