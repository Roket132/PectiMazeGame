#ifndef TASKARCHIVE_H
#define TASKARCHIVE_H

#include <experimental/filesystem>
#include <vector>
#include <mutex>

#include "task.h"

namespace fs = std::experimental::filesystem;

class TaskArchive
{
public:
    TaskArchive();
    TaskArchive(fs::path path);

    bool readFile(fs::path path); // looking for "tasks" in file

    void addTask(std::shared_ptr<Task> task);

    std::shared_ptr<Task> getNextTask();
    std::shared_ptr<Task> getTask(size_t pos);

private:
    std::vector<std::shared_ptr<Task>> tasks;
    size_t currentTask;

    std::mutex* mutex_;
};

#endif // TASKARCHIVE_H
