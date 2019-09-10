#include "maze.h"

#include "engine/Objects/player.h"
#include "engine/Objects/floor.h"
#include "engine/Objects/wall.h"
#include "parsing/parsingtools.h"

#include <fstream>

/*
 * 0 - Free (0)
 * 1 - Wall (1)
 * 2 - Start (2)
 * 3 - Light/Touch (3)
 * 4 - Fog (4)
 * 5 - PectiArrowOpen (5)
 * L - Lion (6)
 * D - Dragon (7)
 * P - PectiArrowClose (8)
 * 9 - Exit (9)
 * B - Fire (10)
 * 66 - Death lion
 * 77 - Death dragon
 * $ - chest (11)
 * 12 - chest_off(12)
 * P - player
 *
 * */

Maze::Maze() {

}

Maze::Maze(fs::path path) {
    std::fstream in;
    try {
        in.open(path.string());
    } catch (std::ifstream::failure e) {
        std::cerr << "error open maze file" << std::endl;
        return;
    }

    in >> h >> w;

    //TODO (if h < 0 || w < 0)

    maze.resize(h, std::vector<MazeObject*>(w));
    enableStartPlaces.clear();

    for (size_t i = 0; i < h; i++) {
        for (size_t j = 0; j < w; j++) {
            static char ch;
            in >> ch;

            //set MazeObject

            if (ch == '#') {
                maze[i][j] = new Wall(QPixmap(":/texture_80/wall/src/texture_80/wall/WallCave.jpg"));
            } else if (ch == '.') {
                maze[i][j] = new Floor(QPixmap(":/texture_80/floor/src/texture_80/floor/floorTile.jpg"));
            } else if (ch == 'S') {
                enableStartPlaces.push_back({{i, j}, true});
                maze[i][j] = new Floor(QPixmap(":/texture_80/floor/src/texture_80/floor/floorTile.jpg"));
            }
        }
    }
    in.close();
}

Maze::Maze(std::string map) {
    Maze(QString::fromStdString(map));
}

Maze::Maze(QString map) {
    std::vector<QString> req = pars::parseRequest(map);
    h = req[1].toInt();
    w = req[2].toInt();
    std::cerr << "new Maze QString: h == " << h << " " << w << std::endl;
    maze.resize(static_cast<size_t>(h), std::vector<MazeObject*>(static_cast<size_t>(w)));



    size_t pos = 3; // first pos_map from [3]
    for (size_t i = 0; i < h; i++) {
        for (size_t j = 0; j < w; j++) {
            if (req[pos] == ".") {
                std::cerr << "req = ." << std::endl;
               maze[i][j] = new Floor(QPixmap(":/texture_80/floor/src/texture_80/floor/floorTile.jpg"));
            } else if (req[pos] == "#") {
                std::cerr << "req = #" << std::endl;
                maze[i][j] = new Wall(QPixmap(":/texture_80/wall/src/texture_80/wall/WallCave.jpg"));
            } else if (req[pos][0] == 'P') {
                std::cerr << "req = P" << std::endl;
                maze[i][j] = new Player(QPixmap(":/res/image/image_40/man_1.jpg"));
            } else {
                std::cerr << "req = else" << std::endl;
                maze[i][j] = new Floor(QPixmap(":/res/image/image_40/lamp.jpg"));
            }
            pos++;
        }
    }
}


int Maze::width() {
    return w;
}

int Maze::height() {
    return h;
}

bool Maze::isPossibleToGoTo(size_t x, size_t y) {
    return (maze[x][y]->getTypeObject() == "floor");
}

MazeObject *Maze::getMazeObject(size_t x, size_t y) {
    return maze[x][y];
}

QString Maze::getTypeObject(size_t x, size_t y) {
    QString type = maze[x][y]->getTypeObject();
    if (type == "player") {
        return "P";
    } else if (type == "wall") {
        return "#";
    } else if (type == "floor") {
        return ".";
    }
}

std::pair<int, int> Maze::getFreeStartPlace() {
    for (auto it : enableStartPlaces) {
        if (it.second) {
            it.second = false;
            return {it.first.first, it.first.second};
        }
    }
    return {-1, -1};
}
