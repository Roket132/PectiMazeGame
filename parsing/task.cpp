#include "task.h"

#include <iostream>

using std::string;
using std::vector;

Task::Task(std::string name, std::string text, std::vector<std::string> answers) :
    name_(name), text_(text)
{
    std::swap(answers_, answers);
}

void Task::setName(std::string name) {
    name_ = name;
}

void Task::setText(std::string text) {
    text_ = text;
}

void Task::addAnswer(std::string ans) {
    answers_.emplace_back(ans);
}


std::string Task::getName() {
    return name_;
}

std::string Task::getText() {
    return text_;
}

std::vector<std::string> *Task::getAnswer() {
    return &answers_;
}
