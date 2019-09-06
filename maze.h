#ifndef MAZE_H
#define MAZE_H

#include "engine/mazeobject.h"
#include "engine/player.h"

#include <QWidget>
#include <vector>
#include <iostream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

class Maze {
public:
    Maze(fs::path path);

    int width();
    int height();
    MazeObject* getMazeObject(size_t x, size_t y);
    std::pair<int, int> getFreeStartPlace();

private:
    int h, w;
    std::vector<std::vector<MazeObject*>> maze;
    std::vector<std::pair<std::pair<int, int>, bool>> enableStartPlaces;
};

#endif // MAZE_H
