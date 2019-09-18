#ifndef LAMP_H
#define LAMP_H

#include "engine/stateobject.h"

class Lamp : public StateObject
{
public:
    Lamp(size_t size);

    const QString TYPE = "lamp";
    QString getTypeObject() override;

private:
    void update() override;
};

#endif // LAMP_H
