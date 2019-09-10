#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include "engine/stateobject.h"

class LightSource : public StateObject
{
public:
    LightSource();
    LightSource(QPixmap texture_, std::vector<QPixmap> *frames = nullptr);

    const QString TYPE = "light_source";
    QString getTypeObject() override;

private:
    void update() override;
};

#endif // LIGHTSOURCE_H
