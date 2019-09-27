#include "enemy.h"

#include "appsettings.h"

Enemy::Enemy(size_t size_, size_t difficulty_, bool dead_) : StateObject (QPixmap(), nullptr), difficulty(difficulty_), size(size_), dead(dead_) {
    isEnemy_ = true;

    if (!setAllTexture(size, difficulty, dead)) {
        setAllTexture(size, difficulty, dead, "png");
    }
}

QString Enemy::getTypeObject() {
    return QStringLiteral("%1%2").arg(difficulty).arg(dead ? 'd' : 'a');
}

QString Enemy::getTypeWitchDifficult() {
    return TYPE + QStringLiteral("_%1").arg(difficulty);
}

size_t Enemy::getDifficulty() {
    return difficulty;
}

bool Enemy::setAllTexture(size_t sisze_, size_t difficulty_, bool dead_, QString imgT) {
    AppSettings &settings = AppSettings::getAppSettings();
    QString stylePrefix = settings.getStyle();

    int sz = static_cast<int>(sisze_);

    def_texture = texture = QPixmap(QStringLiteral(":/%1/src/texture_80/%1/Enemys/enemy_%2_%3.%4")
                                    .arg(stylePrefix).arg(difficulty_).arg(dead_ ? "dead" : "alive").arg(imgT)).scaled(sz, sz);

    return !(def_texture.isNull());
}

void Enemy::kill() {
    possibleStandOnObj = true;
    if (!setAllTexture(size, difficulty, dead = true)) {
        setAllTexture(size, difficulty, dead = true, "png");
    }
}

bool Enemy::isDead() {
    return dead;
}

void Enemy::update() {

}
