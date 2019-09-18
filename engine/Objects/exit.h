#ifndef EXIT_H
#define EXIT_H

#include <engine/stateobject.h>

class Exit : public StateObject {
public:
    Exit(size_t size);
    ~Exit() override = default;

    const QString TYPE = "exit";
    QString getTypeObject() override;

private:
    void update() override;
};

#endif // EXIT_H
