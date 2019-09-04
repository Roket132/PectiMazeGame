#include "dynamicobject.h"

#include <iostream>

DynamicObject::DynamicObject() {
    std::cerr << "yes" << std::endl;
}

DynamicObject::DynamicObject(QPixmap texture_, std::vector<QPixmap> *frames_) : MazeObject (texture_, frames_) {}

DynamicObject::~DynamicObject()
{

}

void DynamicObject::move(int x, int y)
{

}
