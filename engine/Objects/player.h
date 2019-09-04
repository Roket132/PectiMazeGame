#ifndef PLAYER_H
#define PLAYER_H

#include "engine/dynamicobject.h"

#include <QPixmap>

class Player : public DynamicObject {
public:
    Player();
    Player(QPixmap texture_, std::vector<QPixmap> *frames = nullptr);
    ~Player() override;

private:
    void update() override;
};

#endif // PLAYER_H
