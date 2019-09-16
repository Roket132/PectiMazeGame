#ifndef PLAYER_H
#define PLAYER_H

#include "engine/dynamicobject.h"

class Player : public DynamicObject {
public:
    Player(QPixmap texture_, std::vector<QPixmap> *frames = nullptr);
    ~Player() override = default;

    const QString TYPE = "player";
    QString getTypeObject() override;

    void action();

    bool isExtraVis();
    bool isExtraLight();

    void setExtraVision(int time); // set extra vis for @time@ moves
    void setExtraLight(bool set);

    void takePectiArrow();
    bool usePectiArrow(); // return true if pectiArrow use
    int getCntPectiArrow();

private:
    int extraVisionTimer; // if timer == 0 then extraVis  off
    bool extraVision; // if true then player can see more
    bool extraLight; // if true then player has extra light source
    int cntPectiArrow;

    void update() override;
};

#endif // PLAYER_H
