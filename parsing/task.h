#ifndef TASK_H
#define TASK_H

#include <string>
#include <vector>


class Task {
public:
    Task(std::string name = "", std::string text = "", std::vector<std::string> answers = std::vector<std::string>());

    void setName(std::string name);
    void setText(std::string text);

    void addAnswer(std::string ans);

    std::string getName();
    std::string getText();
    std::vector<std::string>* getAnswer();

private:
    std::string name_;

    std::string text_;

    std::vector<std::string> answers_;
};

#endif // TASK_H
