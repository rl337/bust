#ifndef __BUST_TESTING_RUNNER_H__
#define __BUST_TESTING_RUNNER_H__

#include "test.h"
#include "report.h"
#include "suite.h"

namespace bust::testing {

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
