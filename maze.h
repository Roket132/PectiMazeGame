#ifndef MAZE_H
#define MAZE_H

#include "engine/mazeobject.h"

#include <QWidget>
#include <vector>
#include <iostream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

class Maze {
public:
    Maze();
    explicit Maze(fs::path path);
    explicit Maze(std::string map);
    explicit Maze(QString map);

    int width();
    int height();
    MazeObject* getMazeObject(size_t x, size_t y);
    QString getTypeObject(size_t x, size_t y); // Return Type of object in SmallFormat
    std::pair<int, int> getFreeStartPlace();

private:
    int h, w;
    std::vector<std::vector<MazeObject*>> maze;
    std::vector<std::pair<std::pair<int, int>, bool>> enableStartPlaces;
};

#endif // MAZE_H
