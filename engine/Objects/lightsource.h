#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include "engine/stateobject.h"

class LightSource : public StateObject
{
public:
    LightSource(size_t size_);

    const QString TYPE = "light_source";
    QString getTypeObject() override;

private:
    void update() override;
};

#endif // LIGHTSOURCE_H
