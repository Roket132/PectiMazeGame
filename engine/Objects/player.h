#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

#include "engine/dynamicobject.h"

class Player : public DynamicObject {
public:
    Player(size_t size, QPixmap avatar = QPixmap(":/default/src/avatars/default/avatar_1.jpg"));
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
    void setAvatarByType(size_t type);

    std::pair<size_t, size_t> getCurEnemyPos() const;
    void setCurEnemyPos(const std::pair<size_t, size_t> &value);

    void addScore(const long long &add);
    long long getScore();

    bool getExtraVision() const;
    bool getExtraLight() const;

private:
    int extraVisionTimer; // if timer == 0 then extraVis  off
    bool extraVision; // if true then player can see more
    bool extraLight; // if true then player has extra light source
    int cntPectiArrow;

    bool fight;
    size_t enemyDifficulty;
    std::pair<size_t, size_t> curEnemyPos;

    long long score;

    QPixmap avatar;

    void update() override;

public:
    friend std::ostream& operator<< (std::ostream&, const Player&);
    friend std::istream& operator>> (std::istream&, Player&);
};

#endif // PLAYER_H
