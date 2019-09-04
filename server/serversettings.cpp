#include "serversettings.h"


ServerSettings::ServerSettings(fs::path path) : server(nullptr)
{
    maze = createMaze(path);
    std::cerr << "servSet3: " << path.string() << std::endl;
}

ServerSettings &ServerSettings::getServerSettings(fs::path path)
{
    static ServerSettings instance(path);
    return instance;
}

void ServerSettings::startServer()
{
    server = new Server(1337);
}

Maze* ServerSettings::createMaze(std::experimental::filesystem::__cxx11::path path)
{
    if (fs::is_empty(path)) {
        std::cerr << "servSet1: " << path.string() << std::endl;
        maze = nullptr;
        return nullptr;
    }
    std::cerr << "servSet2: " << path.string() << std::endl;
    return new Maze(path);
}

Maze* ServerSettings::getMaze()
{
    return maze;
}
