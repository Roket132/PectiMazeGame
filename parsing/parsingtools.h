#ifndef PARSINGTOOLS_H
#define PARSINGTOOLS_H

#include <vector>
#include <string>
#include <QString>

namespace pars {
    std::vector<QString> splitRequests(QString reqs_);

    std::vector<QString> parseRequest(QString req);
}


#endif // PARSINGTOOLS_H
