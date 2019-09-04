#ifndef STATEOBJECT_H
#define STATEOBJECT_H

#include "mazeobject.h"

class StateObject : public MazeObject
{
public:
    StateObject();
    ~StateObject() override;
protected:
    QPixmap texture;
    std::vector<QPixmap> frames;
};

#endif // STATEOBJECT_H
