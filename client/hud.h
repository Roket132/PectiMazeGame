#ifndef HUD_H
#define HUD_H

#include <vector>
#include <mutex>
#include "engine/mazeobject.h"


class HUD {
public:
    HUD();
    ~HUD();

    void addInventoryObject(MazeObject *obj, int cnt = 1); // *obj will be deleted
    void removeInventoryObject(MazeObject *obj, int cnt = 1); // *obj will be deleted

    void parseRequest(QString req);

public:
    std::vector<std::pair<MazeObject*, int>> inventory;

private:
    std::mutex* mutex_;

};

#endif // HUD_H
