#include "suite.h"

namespace bust::testing {

Suite::Suite(std::string name, bool autodelete) : name(name), autodelete(autodelete) { }
Suite::Suite(std::string name) : name(name), autodelete(false) { }

Suite::~Suite() {
    if (this->autodelete) {
        for(Test *test : tests) {
            delete test;
        }
    }

    tests.clear();
}

void Suite::add(Test *test) {
    tests.push_back(test);
}

void Suite::run(Report *report) {
    for(Test *test : tests) {
        try {
            test->init();
        } catch (std::exception& e) {
            test->error(e.what());
        }

        if (test->getStatus() == None) {
            try {
                test->execute();
            } catch (std::exception& e) {
                test->error(e.what());
            }
        }

        try {
            test->cleanup();
        } catch (std::exception& e) {
            test->error(e.what());
        }

        report->report(this, test);
    }
}

}
