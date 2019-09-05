#include "parsingtools.h"

std::vector<QString> pars::parseRequest(QString req) {
        std::vector<QString> ans;
        QString now = "";
        for (int i = 0; i < req.size(); i++) {
            if (req[i] == ' ') {
                ans.push_back(now);
                now = "";
            } else {
                now += req[i];
            }
        }
        ans.push_back(now);
        return ans;
}

std::vector<QString> pars::splitRequests(QString reqs_)
{
    std::vector<QString> ans;
    QString now = "";
    for (int i = 0; i < reqs_.size(); i++) {
        if (reqs_[i] == ";") {
            ans.push_back(now);
            now = "";
        } else {
            now += reqs_[i];
        }
    }
    return ans;
}
