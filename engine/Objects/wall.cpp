#include "wall.h"

#include "appsettings.h"
#include <iostream>
#include <algorithm>

#include <QPainter>

Wall::Wall(size_t size) : StateObject (QPixmap(), nullptr), size_(size) {
    AppSettings &settings = AppSettings::getAppSettings();
    QString stylePrefix = settings.getStyle();

    if (size <= 40) {
        texture = def_texture = QPixmap(QStringLiteral(":/%1/src/texture_40/%1/wall.jpg").arg(stylePrefix));
    }
    else {
        texture = def_texture = QPixmap(QStringLiteral(":/%1/src/texture_80/%1/wall.jpg").arg(stylePrefix));
    }
}


QString Wall::getTypeObject() {
    return TYPE;
}

void Wall::setShape(MazeObject *up, MazeObject *right, MazeObject *down, MazeObject *left) {

    int cntWalls = 0;
    if (up->getTypeObject() == "wall" || up->getTypeObject() == "fog") cntWalls++;
    if (right->getTypeObject() == "wall" || right->getTypeObject() == "fog") cntWalls++;
    if (down->getTypeObject() == "wall" || down->getTypeObject() == "fog") cntWalls++;
    if (left->getTypeObject() == "wall" || left->getTypeObject() == "fog") cntWalls++;

    AppSettings &settings = AppSettings::getAppSettings();
    QString stylePrefix = settings.getStyle();

    if (!cntWalls) {

        texture = QPixmap(QStringLiteral(":/%1/src/texture_%2/%1/wall4.jpg").arg(stylePrefix).arg(size_));
        return;
    }

    QMatrix mt90, mt180, mt270;
    mt90.rotate(90);
    mt180.rotate(180);
    mt270.rotate(270);

    if (cntWalls == 1) {
        texture = QPixmap(QStringLiteral(":/%1/src/texture_%2/%1/wall3.jpg").arg(stylePrefix).arg(size_));
        if (right->getTypeObject() == "wall" ||
                right->getTypeObject() == "fog") texture = texture.transformed(mt90);
        if (down->getTypeObject() == "wall" ||
                down->getTypeObject() == "fog") texture = texture.transformed(mt180);
        if (left->getTypeObject() == "wall" ||
                left->getTypeObject() == "fog") texture = texture.transformed(mt270);
        return;
    }

    if (cntWalls == 2) {
        if ((left->getTypeObject() != "wall" && right->getTypeObject() != "wall") &&
                (left->getTypeObject() != "fog" && right->getTypeObject() != "fog")) {
            texture = QPixmap(QStringLiteral(":/%1/src/texture_%2/%1/wall5.jpg").arg(stylePrefix).arg(size_));
            return;
        }
        if ((up->getTypeObject() != "wall" && down->getTypeObject() != "wall") &&
                (up->getTypeObject() != "fog" && down->getTypeObject() != "fog"))  {
            texture = texture.transformed(mt180);
            return;
        }
        texture = QPixmap(QStringLiteral(":/%1/src/texture_%2/%1/wall2.jpg").arg(stylePrefix).arg(size_));
        if ((left->getTypeObject() != "wall" && up->getTypeObject() != "wall") &&
                (left->getTypeObject() != "fog" && up->getTypeObject() != "fog"))  texture = texture.transformed(mt90);
        if ((up->getTypeObject() != "wall" && right->getTypeObject() != "wall") &&
                (up->getTypeObject() != "fog" && right->getTypeObject() != "fog"))  texture = texture.transformed(mt180);
        if ((right->getTypeObject() != "wall" && down->getTypeObject() != "wall") &&
                (right->getTypeObject() != "fog" && down->getTypeObject() != "fog")) texture = texture.transformed(mt270);
        return;
    }

    if (cntWalls == 3) {
        texture = QPixmap(QStringLiteral(":/%1/src/texture_%2/%1/wall1.jpg").arg(stylePrefix).arg(size_));

        if (up->getTypeObject() != "wall" &&
                up->getTypeObject() != "fog") texture = texture.transformed(mt90);
        if (right->getTypeObject() != "wall" &&
                right->getTypeObject() != "fog")  texture = texture.transformed(mt180);
        if (down->getTypeObject() != "wall" &&
                down->getTypeObject() != "fog") texture = texture.transformed(mt270);
        return;
    }
    return;
}

void Wall::update() {

}
