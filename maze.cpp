#include "maze.h"

#include <fstream>
#include <queue>

#include "engine/Objects/player.h"
#include "engine/Objects/floor.h"
#include "engine/Objects/wall.h"
#include "engine/Objects/lamp.h"
#include "engine/Objects/fog.h"
#include "engine/Objects/lightsource.h"
#include "engine/Objects/pectiarrow.h"
#include "engine/Objects/pectipatch.h"
#include "engine/Objects/exit.h"

#include "parsing/parsingtools.h"
#include "appsettings.h"



Maze::Maze() {

}

Maze::Maze(fs::path path) {
    // for Server
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
            if (ch == 'S') {
                enableStartPlaces.push_back({{i, j}, true});
                ch = '.';
            }
            maze[i][j] = pars::createObjectByType(pars::getLargeMazeObjectType(ch), 40);
        }
    }
    in.close();

    ShapeWalls();
    bfs(maze, maze_bfs);
}

Maze::Maze(std::string map) {
    Maze(QString::fromStdString(map));
}

Maze::Maze(QString map) {
    // for Client
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
            if (req[pos][0] == 'P') {
                QString style = settings.getStyle();
                size_t typeP = settings.getAvatar();
                maze[i][j] = new Player(80, QPixmap(QStringLiteral(":/%1/src/avatars/%1/avatar_%2.jpg").arg(style).arg(typeP)));
            } else {
                maze[i][j] = pars::createObjectByType(req[pos], 80);
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

void Maze::removeObjectFromCell(size_t x, size_t y) {
    if (x >= static_cast<size_t>(h) || y >= static_cast<size_t>(w)) {
        return;
    } else {
        if (maze[x][y]->getTypeObject() != "wall") {
            delete maze[x][y];
            maze[x][y] = new Floor(40);
        }
    }
}

bool Maze::isPossibleToGoTo(size_t x, size_t y) {
    std::lock_guard<std::mutex> lg(*mutex_);
    return maze[x][y]->possibleToGo();
}

void Maze::bfs(std::vector<std::vector<MazeObject*>> &maze, std::vector<std::vector<int> > &maze_bfs) {
    int D[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
    std::queue<std::pair<size_t, size_t>> q;

    maze_bfs.resize(maze.size(), std::vector<int>(maze[0].size()));

    for (size_t i = 0; i < maze.size(); i++) {
        for (size_t j = 0; j < maze[i].size(); j++) {
            maze_bfs[i][j] = -1;
            if (maze[i][j]->getTypeObject() == "exit") {
                std::cerr << "EXIT ON " << i << " " << j << std::endl;
                maze_bfs[i][j] = 0;
                q.push(std::make_pair(i, j));
            }
        }
    }

    while (!q.empty()) {
        std::pair<size_t, size_t> p = q.front();
        q.pop();
        for (size_t k = 0; k < 4; k++) {
            if (maze[p.first + D[k][0]][p.second + D[k][1]]->getTypeObject() != "wall"
                    && maze_bfs[p.first + D[k][0]][p.second + D[k][1]] == -1)
            {
                q.push(std::make_pair(p.first + D[k][0], p.second + D[k][1]));
                maze_bfs[p.first + D[k][0]][p.second + D[k][1]] = maze_bfs[p.first][p.second] + 1;
            }
        }
    }
}

void Maze::setPectiArrow(size_t x, size_t y, int steps) {
    while (steps--) {
        if (maze[x][y]->getTypeObject() == "floor") {
            delete maze[x][y];
            maze[x][y] = new PectiPatch(40);
        }
        if (maze_bfs[x - 1][y] != -1 && maze_bfs[x - 1][y] < maze_bfs[x][y]) x--;
        else if (maze_bfs[x + 1][y] != -1 && maze_bfs[x + 1][y] < maze_bfs[x][y]) x++;
        else if (maze_bfs[x][y + 1] != -1 && maze_bfs[x][y + 1] < maze_bfs[x][y]) y++;
        else if (maze_bfs[x][y - 1] != -1 && maze_bfs[x][y - 1] < maze_bfs[x][y]) y--;
    }
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
    std::cerr << "Shape " << maze.size() << " " << maze[0].size() << std::endl;
    for (size_t i = 0; i < maze.size(); i++) {
        for (size_t j = 0; j < maze[i].size(); j++) {
            if (maze[i][j]->getTypeObject() == "wall") {
                Wall *wl = dynamic_cast<Wall*>(maze[i][j]);
                MazeObject *up = (i > 0 ? maze[i - 1][j] : maze[i][j]);
                MazeObject *right = (j < maze[i].size() - 1 ? maze[i][j + 1] : maze[i][j]);
                MazeObject *down = (i < maze.size() - 1 ? maze[i + 1][j] : maze[i][j]);
                MazeObject *left = (j > 0 ? maze[i][j - 1] : maze[i][j]);
                std::cerr << up->getTypeObject().toStdString() << " " << right->getTypeObject().toStdString() << " "
                          << down->getTypeObject().toStdString() << " " << left->getTypeObject().toStdString() << std::endl;
                wl->setShape(up, right, down, left);
                std::cerr << "ok " << i << " " << j << std::endl;
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
