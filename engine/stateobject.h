#ifndef STATEOBJECT_H
#define STATEOBJECT_H

#include "mazeobject.h"

class StateObject : public MazeObject
{
public:
    StateObject();

    StateObject(QPixmap texture_, std::vector<QPixmap> *frames_ = nullptr);

    ~StateObject() override;

};

#endif // STATEOBJECT_H
