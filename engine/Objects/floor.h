#ifndef FLOOR_H
#define FLOOR_H

#include "engine/stateobject.h"

class Floor : public StateObject
{
public:
    Floor();

private:
    void update() override;
};

#endif // FLOOR_H
