#ifndef WALL_H
#define WALL_H

#include "engine/stateobject.h"

class Wall : public StateObject
{
public:
    Wall();

private:
    void update() override;
};

#endif // WALL_H
