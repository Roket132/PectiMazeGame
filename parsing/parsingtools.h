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
}


#endif // PARSINGTOOLS_H
