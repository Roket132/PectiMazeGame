#ifndef FOG_H
#define FOG_H

#include "engine/stateobject.h"

class Fog : public StateObject
{
public:
    Fog();
    Fog(QPixmap texture_, std::vector<QPixmap> *frames = nullptr);

    const QString TYPE = "fog";
    QString getTypeObject() override;

private:
    void update() override;
};

#endif // FOG_H
