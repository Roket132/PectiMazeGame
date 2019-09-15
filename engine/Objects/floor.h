#ifndef FLOOR_H
#define FLOOR_H

#include "engine/stateobject.h"

class Floor : public StateObject {
public:
    Floor(size_t size);
    ~Floor() override = default;

    const QString TYPE = "floor";
    QString getTypeObject() override;

private:
    void update() override;
};

#endif // FLOOR_H
