#ifndef __JV_TESTING_RUNNER_H__
#define __JV_TESTING_RUNNER_H__

#include "test.h"
#include "report.h"
#include "suite.h"

namespace testing {

    class Runner {
            std::vector<Suite *> suites;
            MultiReport reports;
            std::string name;

        public:
            Runner();
            ~Runner();

            void add(Suite *s);
            void add(Report *t);

            void run();
    };

}

#endif
