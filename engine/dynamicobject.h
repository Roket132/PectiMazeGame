#ifndef DYNAMICOBJECT_H
#define DYNAMICOBJECT_H

#include "mazeobject.h"

class DynamicObject : public MazeObject {
public:
    DynamicObject();
    DynamicObject(QPixmap texture_, std::vector<QPixmap> *frames = nullptr);
    ~DynamicObject() override;

protected:
    int x_, y_;

public:
    void move(int dx, int dy);

    void moveTo(int x, int y);

    void moveRight();

    void moveLeft();

    void moveDown();

    void moveUp();

    std::pair<int, int> getPlace();
};

#endif // DYNAMICOBJECT_H
