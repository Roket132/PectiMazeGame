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

    virtual QString getTypeObject() = 0; //Return type of object in FullFormata

public:
    QPixmap getTexture();

    bool possibleToGo(); // return possibility stand on this object

    bool isEnemy();
protected:
    QPixmap texture;
    QPixmap def_texture;
    std::vector<QPixmap> frames;

    bool possibleStandOnObj; // can a player stand on this object?
    bool isEnemy_;
};

#endif // MAZEOGJECT_H
