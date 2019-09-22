#include "hud.h"

#include <iostream>
#include <algorithm>

#include "parsing/parsingtools.h"
#include "engine/Objects/lamp.h"
#include "engine/Objects/pectiarrow.h"
#include "appsettings.h"

HUD::HUD() : mutex_(new std::mutex) {
}

HUD::~HUD() {
    for (auto it : inventory) {
        delete it.first;
    }
}


void HUD::addInventoryObject(MazeObject *obj, int cnt) {
    std::lock_guard<std::mutex> lg(*mutex_);
    if (obj == nullptr) return;

    bool added = false;
    for (auto &it : inventory) {
        if (it.first->getTypeObject() == obj->getTypeObject()) {
            it.second += cnt;
            added = true;
        }
    }

    if (!added) {
        if (obj->getTypeObject() == "lamp") {
            inventory.insert(inventory.begin(), {obj, cnt});
        }
        else {
            inventory.push_back({obj, cnt});
        }
    } else {
        delete obj;
    }
}

void HUD::removeInventoryObject(MazeObject *obj, int cnt) {
    std::lock_guard<std::mutex> lg(*mutex_);
    if (obj == nullptr) return;
    int pos = 0;
    for (auto &it : inventory) {
        if (it.first->getTypeObject() == obj->getTypeObject()) {
            it.second = std::max(0, it.second - cnt);
            if (it.second == 0) {
                delete it.first;
                inventory.erase(inventory.begin() + pos);
            }
        }
        pos++;
    }
}

void HUD::parseRequest(QString req_) {
    std::vector<QString> req = pars::parseRequest(req_);
    if (req[1] == "add") {
        MazeObject* obj = pars::createObjectByType(req[2], 80);
        addInventoryObject(obj, req[3].toInt());
    } else if (req[1] == "del") {
        MazeObject* obj = pars::createObjectByType(req[2], 80);
        removeInventoryObject(obj, req[3].toInt());
    }
}

void HUD::restoreInventory(QString req_) {
    AppSettings &settings = AppSettings::getAppSettings();
    std::vector<QString> req = pars::parseRequest(req_);
    settings.setAvatar(req[1].toUInt());
    if (req[2].toInt()) addInventoryObject(new Lamp(80));
    for (int i = 0; i < req[3].toInt(); i++) {
        addInventoryObject(new PectiArrow(80));
    }
}
