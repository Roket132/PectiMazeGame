#ifndef MAZE_H
#define MAZE_H

#include "engine/mazeobject.h"

#include <mutex>
#include <vector>
#include <iostream>
#include <experimental/filesystem>
#include <QWidget>

namespace fs = std::experimental::filesystem;

class Maze {
public:
    Maze();
    explicit Maze(fs::path path); // create maze for server with @40@ size

    explicit Maze(std::string map); // convert string to QString and call Maze(QString)
    explicit Maze(QString map); // create maze for client with @80@ size

    ~Maze();

    MazeObject* getMazeObject(size_t x, size_t y);
    QString getTypeObject(size_t x, size_t y); // Return Type of object in SmallFormat
    std::pair<int, int> getFreeStartPlace();

    int width();
    int height();
    void removeObjectFromCell(size_t x, size_t y);
    bool isPossibleToGoTo(size_t x, size_t y);

    void bfs(std::vector<std::vector<MazeObject*>> &maze, std::vector<std::vector<int>> &maze_bfs);
    void setPectiArrow(size_t x, size_t y, int steps = 10);

    int enemyAttack(size_t x, size_t y);

private:
    int h, w;
    std::vector<std::vector<MazeObject*>> maze;
    std::vector<std::vector<int>> maze_bfs;
    std::vector<std::pair<std::pair<int, int>, bool>> enableStartPlaces;

    void ShapeWalls();
    void ShapeFog();

    std::mutex* mutex_;
};

#endif // MAZE_H
