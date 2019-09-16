#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QLabel>
#include <vector>

#include "client/clientsettings.h"
#include"server/serversettings.h"
#include "engine/mazeobject.h"

class Engine : public QObject {
Q_OBJECT
public:
    explicit Engine(std::vector<QLabel*> scenes_);
    explicit Engine(std::vector<QLabel*> scenes_, std::vector<QLabel*> invScenes_);

    void stopEngine();

private:
    std::vector<QLabel*> scenes;
    std::vector<QLabel*> invScenes;

    bool _STOP_ = false;

public slots:
     void drawClientMap();

     void drawServerMap();
};

#endif // ENGINE_H
