#include "stateobject.h"
StateObject::StateObject()
{

}

StateObject::StateObject(QPixmap texture_, std::vector<QPixmap> *frames_) : MazeObject (texture_, frames_){}



StateObject::~StateObject()
{

}
