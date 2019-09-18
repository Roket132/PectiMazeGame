#include "parsingtools.h"

#include "engine/Objects/player.h"
#include "engine/Objects/floor.h"
#include "engine/Objects/wall.h"
#include "engine/Objects/lamp.h"
#include "engine/Objects/fog.h"
#include "engine/Objects/lightsource.h"
#include "engine/Objects/pectiarrow.h"
#include "engine/Objects/pectipatch.h"

std::vector<QString> pars::parseRequest(QString req) {
        std::vector<QString> ans;
        QString now = "";
        for (int i = 0; i < req.size(); i++) {
            if (req[i] == ' ') {
                ans.push_back(now);
                now = "";
            } else {
                now += req[i];
            }
        }
        ans.push_back(now);
        return ans;
}

std::vector<QString> pars::splitRequests(QString reqs_)
{
    std::vector<QString> ans;
    QString now = "";
    for (int i = 0; i < reqs_.size(); i++) {
        if (reqs_[i] == ";") {
            ans.push_back(now);
            now = "";
        } else {
            now += reqs_[i];
        }
    }
    return ans;
}

MazeObject *pars::createObjectByType(QString type, size_t size_) {
    if (type == "floor") return new Floor(size_);
    if (type == "pecti_arrow") return new PectiArrow(size_);
    if (type == "pecti_patch") return new PectiPatch(size_);
    if (type == "lamp") return new Lamp(size_);
    if (type == "light_source") return new LightSource(size_);
    if (type == "wall") return new Wall(size_);
    if (type == "fog") return new Fog(size_);
    return nullptr;
}
