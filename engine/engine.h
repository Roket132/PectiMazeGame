#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QPushButton>
#include <QLabel>
#include <vector>

#include "client/clientsettings.h"
#include"server/serversettings.h"
#include "engine/mazeobject.h"

class Engine : public QObject {
Q_OBJECT
public:
    explicit Engine(std::vector<QLabel*> scenes_);
    explicit Engine(std::vector<QLabel*> scenes_, std::vector<QPushButton*> invScenes_);
    explicit Engine(std::vector<QLabel*> scenes_, std::vector<QPushButton*> invScenes_, std::vector<QLabel*> infoInvScenes_);

    void stopEngine();

private:
    std::vector<QLabel*> scenes;
    std::vector<QPushButton*> invScenes;
    std::vector<QLabel*> infoInvScenes;

    bool _STOP_ = false;

public slots:
     void drawClientMap();

     void drawServerMap();
};

#endif // ENGINE_H
