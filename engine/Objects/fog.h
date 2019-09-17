#ifndef FOG_H
#define FOG_H

#include "engine/stateobject.h"

class Fog : public StateObject
{
public:
    Fog(size_t size_);

    const QString TYPE = "fog";
    QString getTypeObject() override;

    void makeShape(QString type, int number);

private:
    void update() override;

    size_t size_;
};

#endif // FOG_H
