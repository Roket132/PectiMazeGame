#ifndef LAMP_H
#define LAMP_H

#include "engine/stateobject.h"

class Lamp : public StateObject
{
public:
    Lamp();
    Lamp(QPixmap texture_, std::vector<QPixmap> *frames = nullptr);

    const QString TYPE = "lamp";
    QString getTypeObject() override;

private:
    void update() override;
};

#endif // LAMP_H
