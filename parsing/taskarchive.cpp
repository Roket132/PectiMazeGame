#include "taskarchive.h"

#include <iostream>
#include <fstream>

using std::unique_ptr;

TaskArchive::TaskArchive() : currentTask(0) {

}

TaskArchive::TaskArchive(std::experimental::filesystem::__cxx11::path path) :currentTask()  {
    readFile(path);
}

namespace {

    void removeLeadSpaces(std::string &str) {
        std::reverse(str.begin(), str.end());
        while (str.back() == ' ') str.pop_back();
        std::reverse(str.begin(), str.end());
    }

}

bool TaskArchive::readFile(std::experimental::filesystem::__cxx11::path path) {
    std::fstream file;
    try {
        file.open(path.string());
    } catch (std::ifstream::failure e) {
        std::cerr << "Cannot readFile for TaskArchive" << std::endl;
        return false;
    }

    constexpr size_t bufferSize = 1024;
    unique_ptr<char[]> buffer(new char[bufferSize]);

    static const int NAME = 1;
    static const int TASK = 2;
    static const int ANSWER = 3;
    int mode = 0;

    std::string name;
    std::string task;
    std::string answer;
    std::vector<std::string> answers;

    while (file) {
        file.read(buffer.get(), bufferSize);

        for (size_t i = 0; i < bufferSize; i++) {
            if (buffer.get()[i] == '<') {
                mode = NAME;
            } else if (buffer.get()[i] == '{') {
                mode = TASK;
            } else if (buffer.get()[i] == '[') {
                mode = ANSWER;
            } else if (buffer.get()[i] == '>' || buffer.get()[i] == '}') {
                mode = 0;
            } else if (buffer.get()[i] == ']') {
                mode = 0;
                tasks.push_back(std::make_shared<Task>(Task(name, task, answers)));
                name = task = answer = "";
                answers.clear();
            } else if (buffer.get()[i] == ',') {
                removeLeadSpaces(answer);
                answers.emplace_back(answer);
                answer = "";
            } else {
                char ch = buffer.get()[i];
                if (mode == NAME) name += ch;
                if (mode == TASK) task += ch;
                if (mode == ANSWER) answer += ch;
            }
        }
    }
}

std::shared_ptr<Task> TaskArchive::getNextTask() {
    if (currentTask >= tasks.size()) return nullptr;
    return tasks[currentTask++];
}
