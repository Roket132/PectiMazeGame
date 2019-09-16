#ifndef PECTIARROW_H
#define PECTIARROW_H

#include "engine/stateobject.h"

class PectiArrow : public StateObject {
public:
    PectiArrow(size_t size);
    ~PectiArrow() override = default;

    const QString TYPE = "pecti_arrow";
    QString getTypeObject() override;

private:
    void update() override;
};

#endif // PECTIARROW_H
