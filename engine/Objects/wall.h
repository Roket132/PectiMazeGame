#ifndef WALL_H
#define WALL_H

#include "engine/stateobject.h"

#include <QPixmap>

class Wall : public StateObject
{
public:
    Wall(size_t size);

    const QString TYPE = "wall";
    QString getTypeObject() override;

    void setShape(MazeObject *up, MazeObject *right, MazeObject *down, MazeObject *left);

private:
    size_t size_;

    void update() override;
};

#endif // WALL_H
