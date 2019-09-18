#include "maze.h"

#include "engine/Objects/player.h"
#include "engine/Objects/floor.h"
#include "engine/Objects/wall.h"
#include "engine/Objects/lamp.h"
#include "engine/Objects/fog.h"
#include "engine/Objects/lightsource.h"
#include "engine/Objects/pectiarrow.h"
#include "engine/Objects/pectipatch.h"

#include "parsing/parsingtools.h"
#include "appsettings.h"

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

    mutex_ = new std::mutex;
    std::lock_guard<std::mutex> lg(*mutex_);

    AppSettings &settings = AppSettings::getAppSettings();
    QString stylePrefix = settings.getStyle();

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
                maze[i][j] = new Wall(40);
            } else if (ch == '.') {
                maze[i][j] = new Floor(40);
            } else if (ch == 'S') {
                enableStartPlaces.push_back({{i, j}, true});
                maze[i][j] = new Floor(40);
            } else if (ch == 'T') {
                maze[i][j] = new Lamp(40);
            } else if (ch == 'B') {
                maze[i][j] = new LightSource(40);
            } else if (ch == 'P') {
                maze[i][j] = new PectiArrow(40);
            }
        }
    }
    in.close();

    ShapeWalls();
}

Maze::Maze(std::string map) {
    Maze(QString::fromStdString(map));
}

Maze::Maze(QString map) {
    mutex_ = new std::mutex;
    std::lock_guard<std::mutex> lg(*mutex_);

    AppSettings &settings = AppSettings::getAppSettings();
    QString stylePrefix = settings.getStyle();

    std::vector<QString> req = pars::parseRequest(map);
    h = req[1].toInt();
    w = req[2].toInt();
    maze.resize(static_cast<size_t>(h), std::vector<MazeObject*>(static_cast<size_t>(w)));

    size_t pos = 3; // first pos_map from [3]
    for (size_t i = 0; i < h; i++) {
        for (size_t j = 0; j < w; j++) {
            if (req[pos] == "floor") {
               maze[i][j] = new Floor(80);
            } else if (req[pos] == "wall") {
                maze[i][j] = new Wall(80);
            } else if (req[pos][0] == 'P') {

                // TODO add different players ??

                maze[i][j] = new Player(QPixmap(":/res/image/image_80/man_1.jpg"));
            } else if (req[pos] == "light_source") {
                maze[i][j] = new LightSource(80);
            } else if(req[pos] == "lamp") {
                maze[i][j] = new Lamp(80);
            } else if (req[pos] == "fog") {
                maze[i][j] = new Fog(80);
            } else if (req[pos] == "pecti_arrow") {
                maze[i][j] = new PectiArrow(80);
            } else if (req[pos] == "pecti_patch") {
                maze[i][j] = new PectiPatch(80);
            } else {
                maze[i][j] = new Wall(80);
            }
            pos++;
        }
    }
    ShapeWalls();
    ShapeFog();
}

Maze::~Maze() {
    std::lock_guard<std::mutex> lg(*mutex_);
    for (auto raw : maze) {
        for (auto it : raw) {
            delete it;
        }
    }
    maze.clear();
}


int Maze::width() {
    std::lock_guard<std::mutex> lg(*mutex_);
    return w;
}

int Maze::height() {
    std::lock_guard<std::mutex> lg(*mutex_);
    return h;
}

bool Maze::isPossibleToGoTo(size_t x, size_t y) {
    std::lock_guard<std::mutex> lg(*mutex_);
    return maze[x][y]->possibleToGo();
}

MazeObject *Maze::getMazeObject(size_t x, size_t y) {
    std::lock_guard<std::mutex> lg(*mutex_);
    return maze[x][y];
}

QString Maze::getTypeObject(size_t x, size_t y) {
    std::lock_guard<std::mutex> lg(*mutex_);
    return maze[x][y]->getTypeObject();
}

std::pair<int, int> Maze::getFreeStartPlace() {
    std::lock_guard<std::mutex> lg(*mutex_);
    for (auto &it : enableStartPlaces) {
        if (it.second) {
            it.second = false;
            return {it.first.first, it.first.second};
        }
    }
    return {-1, -1};
}

void Maze::ShapeWalls() {
    std::cerr << "Shape " << maze.size() << std::endl;
    for (size_t i = 0; i < maze.size(); i++) {
        for (size_t j = 0; j < maze[i].size(); j++) {
            if (maze[i][j]->getTypeObject() == "wall") {
                Wall *wl = dynamic_cast<Wall*>(maze[i][j]);
                MazeObject *up = (i > 0 ? maze[i - 1][j] : maze[i][j]);
                MazeObject *right = (j < maze[i].size() - 1 ? maze[i][j + 1] : maze[i][j]);
                MazeObject *down = (i < maze.size() - 1 ? maze[i + 1][j] : maze[i][j]);
                MazeObject *left = (j > 0 ? maze[i][j - 1] : maze[i][j]);
                wl->setShape(up, right, down, left);
            }
        }
    }
}

void Maze::ShapeFog() {
    size_t i = 0, j = 0;
    int type = 3;
    while (j < maze[i].size()) {
        if (maze[i][j]->getTypeObject() == "fog") {
            Fog *fg = dynamic_cast<Fog*>(maze[i][j++]);
            fg->makeShape("down", type);
            if (!--type) type = 3;
        } else return; // because fog only on border
    }

    type = 3; j--;
    while (i < maze.size()) {
        Fog *fg = dynamic_cast<Fog*>(maze[i++][j]);
        fg->makeShape("left", type);
        if (!--type) type = 3;
    }
    type = 3; i--;
    while (true) {
        Fog *fg = dynamic_cast<Fog*>(maze[i][j]);
        fg->makeShape("up", type);
        if (!--type) type = 3;
        if (j == 0) break; else j--;
    }
    type = 3;
    while (true) {
        Fog *fg = dynamic_cast<Fog*>(maze[i][j]);
        fg->makeShape("right", type);
        if (!--type) type = 3;
        if (i == 0) break; else i--;
    }
    size_t he = static_cast<size_t>(h - 1);
    size_t wi = static_cast<size_t>(w - 1);
    Fog *fgd = dynamic_cast<Fog*>(maze[0][0]);
    Fog *fgu = dynamic_cast<Fog*>(maze[he][wi]);
    Fog *fgr = dynamic_cast<Fog*>(maze[he][0]);
    Fog *fgl = dynamic_cast<Fog*>(maze[0][wi]);
    fgd->makeShape("down", 0); fgu->makeShape("up", 0);
    fgl->makeShape("left", 0); fgr->makeShape("right", 0);
}
