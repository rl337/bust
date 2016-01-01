#include "suite.h"
#include <string>

namespace testing {

Suite::Suite(std::string name) : name(name) { }

Suite::~Suite() {
    // std::vector destroys contents when clears.
    // no need to delete explicitly.
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
