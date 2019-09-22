#ifndef PARSINGTOOLS_H
#define PARSINGTOOLS_H

#include <vector>
#include <string>
#include <QString>
#include "engine/mazeobject.h"

namespace pars {
    std::vector<QString> splitRequests(QString reqs_);

    std::vector<QString> parseRequest(QString req);

    MazeObject* createObjectByType(QString type, size_t size_);

    MazeObject* createEnemyByType(size_t difficulty, size_t size_, bool dead_ = false);

    QString getLargeMazeObjectType(char ch);

}


#endif // PARSINGTOOLS_H
