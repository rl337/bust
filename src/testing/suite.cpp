#include "suite.h"
#include <string>

namespace jarvis_testing {

Suite::Suite(std::string name) : name(name) { }

void Suite::add(Test *test) {
    tests.push_back(test);
}

void Suite::run() {
    for(Test *test : tests) {
        try {
            test->init();
        } catch (std::exception& e) {
            test->error(e.what());
        }

        if (test->getStatus() == None) {
            try {
                test->run();
            } catch (std::exception& e) {
                test->error(e.what());
            }
        }

        try {
            test->cleanup();
        } catch (std::exception& e) {
            test->error(e.what());
        }

    }
}

}
