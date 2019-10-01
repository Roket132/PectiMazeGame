#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <vector>

#include "client/clientsettings.h"
#include"server/serversettings.h"
#include "engine/mazeobject.h"

class ServerWindow;

class Engine : public QObject {
Q_OBJECT
public:
    explicit Engine(std::vector<QLabel*> scenes_, ServerWindow* window);
    explicit Engine(std::vector<QLabel*> scenes_, std::vector<QPushButton*> invScenes_, std::vector<QLabel*> infoInvScenes_, QLabel* s_lay);

    void stopEngine();

private:
    std::vector<QLabel*> scenes;
    std::vector<QPushButton*> invScenes;
    std::vector<QLabel*> infoInvScenes;

    QLabel* score;

    ServerWindow* serverWindow;

    bool _STOP_ = false;

public slots:
     void drawClientMap();

     void drawServerMap();
};

#endif // ENGINE_H
