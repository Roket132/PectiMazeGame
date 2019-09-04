#ifndef DYNAMICOBJECT_H
#define DYNAMICOBJECT_H

#include "mazeobject.h"

class DynamicObject : public MazeObject
{
public:
    DynamicObject();
    ~DynamicObject() override;

protected:
    void move(int x, int y);
};

#endif // DYNAMICOBJECT_H
