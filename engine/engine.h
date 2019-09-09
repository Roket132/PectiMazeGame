#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QLabel>
#include <vector>

#include "client/clientsettings.h"
#include "engine/mazeobject.h"

class Engine : public QObject {
Q_OBJECT
public:
    explicit Engine(std::vector<QLabel*> scenes_);

private:
    std::vector<QLabel*> scenes;

public slots:
    void drawClientMap();
};

#endif // ENGINE_H
