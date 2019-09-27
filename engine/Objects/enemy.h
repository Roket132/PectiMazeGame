#ifndef ENEMY_H
#define ENEMY_H

#include "engine/stateobject.h"

class Enemy : public StateObject {
public:
    Enemy(size_t size, size_t difficulty_, bool dead_);
    ~Enemy() override = default;

    const QString TYPE = "enemy";
    QString getTypeObject() override;

    QString getTypeWitchDifficult();
    size_t getDifficulty();

    void kill();
    bool isDead();

private:
    size_t difficulty;
    size_t size;
    bool dead;

    bool setAllTexture(size_t size_, size_t difficulty_, bool dead_, QString imgType = "jpg");

    void update() override;
};

#endif // ENEMY_H
