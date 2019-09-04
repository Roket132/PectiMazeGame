#ifndef FLOOR_H
#define FLOOR_H

#include "engine/stateobject.h"

class Floor : public StateObject
{
public:
    Floor();
    Floor(QPixmap texture_, std::vector<QPixmap> *frames = nullptr);
    ~Floor() override = default;

private:
    void update() override;
};

#endif // FLOOR_H
