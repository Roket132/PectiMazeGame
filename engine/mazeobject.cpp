#include "mazeobject.h"

MazeObject::MazeObject()
{

}

MazeObject::MazeObject(QPixmap texture_, std::vector<QPixmap> *frames_)
{
    texture = texture_;
    if (frames_ != nullptr) {
        frames.clear();
        for (auto it : *frames_) {
            frames.push_back(it);
        }
    }
}

QPixmap MazeObject::getTexture()
{
    return texture;
}

