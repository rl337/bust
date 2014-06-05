#include <iostream>
#include "report.h"

namespace jarvis_testing {

    class StdoutReport : public Report {

        void report(Test *t) {
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

    };

}
