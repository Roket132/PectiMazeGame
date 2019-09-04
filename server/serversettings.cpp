#include "serversettings.h"

ServerSettings::ServerSettings(fs::path path) : server(nullptr)
{
    maze = new Maze(path);
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
        maze = nullptr;
        return nullptr;
    }
    return new Maze(path);
}

Maze* ServerSettings::getMaze()
{
    return maze;
}
