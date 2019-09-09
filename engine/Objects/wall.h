#ifndef WALL_H
#define WALL_H

#include "engine/stateobject.h"

#include <QPixmap>

class Wall : public StateObject
{
public:
    Wall();
    Wall(QPixmap texture_, std::vector<QPixmap> *frames = nullptr);

    const QString TYPE = "wall";
    QString getTypeObject() override;

private:
    void update() override;
};

#endif // WALL_H
