#ifndef SERVERSETTINGS_H
#define SERVERSETTINGS_H

#include "maze.h"
#include "server.h"

#include <QWidget>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

/*
 * Singleton object
 */

class ServerSettings {
public:
    static ServerSettings &getServerSettings(fs::path path = "");

    void startServer();
    Maze* createMaze(fs::path);
    Maze* getMaze();


private:
    ServerSettings(fs::path path);
    ~ServerSettings() {}
    ServerSettings& operator=(ServerSettings&) = delete;
    ServerSettings(const ServerSettings&) = delete;

private:
    Server *server;
    Maze   *maze;

};

#endif // SERVERSETTINGS_H
