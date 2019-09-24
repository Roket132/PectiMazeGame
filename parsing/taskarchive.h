#ifndef TASKARCHIVE_H
#define TASKARCHIVE_H

#include <vector>
#include "task.h"
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

class TaskArchive
{
public:
    TaskArchive();
    TaskArchive(fs::path path);

    bool readFile(fs::path path); // looking for "tasks" in file

    std::shared_ptr<Task> getNextTask();

private:
    std::vector<std::shared_ptr<Task>> tasks;

    size_t currentTask;
};

#endif // TASKARCHIVE_H
