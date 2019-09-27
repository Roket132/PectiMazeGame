#ifndef PLAYER_H
#define PLAYER_H

#include "engine/dynamicobject.h"

class Player : public DynamicObject {
public:
    Player(size_t size, QPixmap avatar = QPixmap(":/default/src/avatars/default/avatar_1.jpg"));
    Player(QPixmap texture_, std::vector<QPixmap> *frames = nullptr);
    ~Player() override = default;

    const QString TYPE = "player";
    QString getTypeObject() override;

    void action();

    bool isExtraVis();
    bool isFight();
    bool isExtraLight();

    void setExtraVision(int time); // set extra vis for @time@ moves
    void setExtraLight(bool set);
    void setFight(bool set, size_t enemyDifficulty);

    void takePectiArrow();
    bool usePectiArrow(); // return true if pectiArrow use

    int getCntPectiArrow();
    int getExtraVisTimer();
    size_t getEnemyDifficulty();

    bool canMove();

    QPixmap getAvatar();

    std::pair<size_t, size_t> getCurEnemyPos() const;
    void setCurEnemyPos(const std::pair<size_t, size_t> &value);

private:
    int extraVisionTimer; // if timer == 0 then extraVis  off
    bool extraVision; // if true then player can see more
    bool extraLight; // if true then player has extra light source
    int cntPectiArrow;

    bool fight;
    size_t enemyDifficulty;
    std::pair<size_t, size_t> curEnemyPos;

    QPixmap avatar;

    void update() override;
};

#endif // PLAYER_H
