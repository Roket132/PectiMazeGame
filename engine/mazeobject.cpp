#include "mazeobject.h"

MazeObject::MazeObject() {
    def_texture = QPixmap(":/res/image/image_80/red.jpg");
}

MazeObject::MazeObject(QPixmap texture_, std::vector<QPixmap> *frames_) {
    texture = def_texture = texture_;
    if (frames_ != nullptr) {
        frames.clear();
        for (auto it : *frames_) {
            frames.push_back(it);
        }
    }
}

QPixmap MazeObject::getTexture() {
    return (texture.isNull() ? def_texture : texture);
}

