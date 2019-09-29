#include "engine.h"

#include <thread>
#include "client/hud.h"

Engine::Engine(std::vector<QLabel*> scenes_) : scenes(scenes_) {}

Engine::Engine(std::vector<QLabel *> scenes_, std::vector<QPushButton *> invScenes_, std::vector<QLabel *> infoInvScenes_, QLabel* s_lay) :
    scenes(scenes_), invScenes(invScenes_), infoInvScenes(infoInvScenes_), score(s_lay) {}

void Engine::stopEngine() {
    _STOP_ = true;
}

void Engine::drawClientMap() {
    ClientSettings &client = ClientSettings::getClientSettings();

    while (true) {
        if (_STOP_) return;

        HUD *hud = client.getHUD();

        for (size_t i = 0; i < 3; i++) {
            invScenes[i]->setIcon(QIcon());
            infoInvScenes[i]->setText("");
        }

        //points

        score->setText(QString("Очков: %1").arg(hud->getPoints()));

        //inventory

        size_t used = 0;
        for (auto it : hud->inventory) {
            invScenes[used]->setIcon(it.first->getTexture());
            invScenes[used]->setObjectName(it.first->getTypeObject());
            infoInvScenes[used]->setText("");
            if (it.first->getTypeObject() != "lamp") {
                infoInvScenes[used]->setText(QStringLiteral("    Осталcя: %1\n").arg(it.second));
            }
            used++;
            if (used == 3) break;
        }

        Maze* maze = client.getMaze();
        size_t curScene = 0;        

        if (maze == nullptr) continue;
        for (int i = 0; i < maze->height(); i++) {
            for (int j = 0; j < maze->width(); j++) {
                MazeObject* Object = maze->getMazeObject(static_cast<size_t>(i), static_cast<size_t>(j));
                scenes[curScene++]->setPixmap(Object->getTexture());
            }
        }
        std::this_thread::sleep_for (std::chrono::milliseconds(100));
    }

}

void Engine::drawServerMap() {
    ServerSettings &server = ServerSettings::getServerSettings();
    while (true) {
        if (_STOP_) return;

        Maze* maze = server.getMaze();
        size_t curScene = 0;

        for (int i = 0; i < 25; i++) {
            for (int j = 0; j < 25; j++) {
                if (i >= maze->height() || j >= maze->width()) {
                    //TODO set default picture
                    curScene++;
                    continue;
                }
                Player* player = server.isPlayer(i, j);
                if (player != nullptr) {
                    scenes[curScene++]->setPixmap(player->getTexture());
                } else {
                    MazeObject* Object = maze->getMazeObject(i, j);
                    scenes[curScene++]->setPixmap(Object->getTexture());
                }
            }
        }
        std::this_thread::sleep_for (std::chrono::milliseconds(100));
    }
}

