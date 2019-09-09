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
        std::this_thread::sleep_for (std::chrono::milliseconds(9000));
    }

}
