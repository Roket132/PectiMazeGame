#include "engine.h"

#include <thread>


Engine::Engine(std::vector<QLabel*> scenes_) : scenes(scenes_) {

}



void Engine::drawClientMap() {
    ClientSettings &client = ClientSettings::getClientSettings();

    while (true) {
        size_t curScene = 0;
        Maze* maze = client.getMaze();
        if (maze == nullptr) continue;
        for (int i = 0; i < maze->height(); i++) {
            for (int j = 0; j < maze->height(); j++) {
                MazeObject* Object = maze->getMazeObject(static_cast<size_t>(i), static_cast<size_t>(j));
                scenes[curScene++]->setPixmap(Object->getTexture());
            }
        }
        std::this_thread::sleep_for (std::chrono::milliseconds(2000));
    }

}

void Engine::drawServerMap() {
    ServerSettings &server = ServerSettings::getServerSettings();
    while (true) {
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
        std::this_thread::sleep_for (std::chrono::milliseconds(1000));
    }
}

