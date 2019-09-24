#ifndef PARSINGTOOLS_H
#define PARSINGTOOLS_H

#include <vector>
#include <string>
#include <QString>

#include "engine/mazeobject.h"
#include "taskarchive.h"

namespace pars {
    std::vector<QString> splitRequests(QString reqs_);

    std::vector<QString> parseRequest(QString req);

    std::vector<QString> parseRequest(QString req, int cnt);

    MazeObject* createObjectByType(QString type, size_t size_);

    MazeObject* createEnemyByType(size_t difficulty, size_t size_, bool dead_ = false);

    QString getLargeMazeObjectType(char ch);

    QString prepareTaskForSend(std::shared_ptr<Task> task);

}


#endif // PARSINGTOOLS_H
