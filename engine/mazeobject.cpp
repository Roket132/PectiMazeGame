#include "mazeobject.h"

MazeObject::MazeObject(QPixmap texture_, std::vector<QPixmap> *frames_)
{
    texture = texture_;
    frames.clear();
    for (auto it : *frames_) {
        frames.push_back(it);
    }
}

QPixmap MazeObject::getTexture()
{
    return texture;
}

