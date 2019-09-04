#include "maze.h"

#include "engine/Objects/floor.h"
#include "engine/Objects/player.h"
#include "engine/Objects/wall.h"

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
 *
 *
 * */

Maze::Maze(fs::path path)
{
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
                maze[i][j] = new Wall(QPixmap(":/res/image/image_40/wall.jpg"));
            } else if (ch == '.') {
                maze[i][j] = new Floor(QPixmap(":/res/image/image_40/PectPatchi40.png"));
            } else {
                //maze[i][j] = ch - '0';
            }
        }
    }
    in.close();
}


int Maze::width()
{
    return w;
}

int Maze::height()
{
    return h;
}

MazeObject *Maze::getMazeObject(size_t x, size_t y)
{
    return maze[x][y];
}
