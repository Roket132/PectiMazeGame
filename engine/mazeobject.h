#ifndef MAZEOGJECT_H
#define MAZEOGJECT_H

#include <QPixmap>

/*
 * Object which can be draw
 */

class MazeObject {
public:
    MazeObject();
    MazeObject(QPixmap texture_, std::vector<QPixmap> *frames = nullptr);

    virtual ~MazeObject() = default;

    virtual void update() = 0;

    QPixmap getTexture();

protected:
    QPixmap texture;
    std::vector<QPixmap> frames;


};

#endif // MAZEOGJECT_H
