#ifndef PECTIPATCH_H
#define PECTIPATCH_H

#include "engine/stateobject.h"

class PectiPatch : public StateObject {
public:
    PectiPatch(size_t size);
    ~PectiPatch() override = default;

    const QString TYPE = "pecti_patch";
    QString getTypeObject() override;

private:
    void update() override;
};

#endif // PECTIPATCH_H
