#ifndef PLAYER_H
#define PLAYER_H

#include "mazeobject.h"

#include <QPixmap>

class Player : MazeObject {
public:
    Player(QPixmap texture_, std::vector<QPixmap> *frames);
};

#endif // PLAYER_H
