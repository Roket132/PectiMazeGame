#ifndef LIGHT_H
#define LIGHT_H

#include "engine/stateobject.h"

class Light : public StateObject
{
public:
    Light();
    Light(QPixmap texture_, std::vector<QPixmap> *frames = nullptr);

    const QString TYPE = "light";
    QString getTypeObject() override;

private:
    void update() override;
};

#endif // LIGHT_H
