#include <iostream>
#include "report.h"

namespace testing {

    void StdoutReport::report(Suite *s, Test *t) {
        if (t == NULL) {
            std::cout << "TEST WAS NULL" << std::endl;
            return;
        }

        std::string name = t->getName();
        if (name.length() < 1) {
            name = "Unnamed";
        }

        std::string status;
        switch(t->getStatus()) {
            case None:
                status = "N";
                break;
            case Pass:
                status = ".";
                break;
            case Fail:
                status = "F";
                break;
            case Abort:
                status = "A";
                break;
            case Error:
                status = "E";
                break;
            case Skip:
                status = "S";
                break;
            default:
                status = "X";
        }

        std::string mesg = t->getMessage();
        if (mesg.length() < 1) {
            mesg = "No Message";
        }

        std::cout << status << " " << name << ": " << mesg << std::endl;
    }

    void MultiReport::add(Report *report) {
        this->reports.push_back(report);
    }

    void MultiReport::report(Suite *s, Test *t) {
        for (Report *report : reports) {
            report->report(s, t);
        }
    }
}
