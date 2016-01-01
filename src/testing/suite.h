#ifndef __JV_TESTING_SUITE_H__
#define __JV_TESTING_SUITE_H__

#include <string>
#include <vector>

#include "test.h"
#include "report.h"

namespace testing {

    class Report;

    class Suite {
            std::vector<Test *> tests;
            std::string name;

        public:
            Suite(std::string name);
            ~Suite();

            void add(Test *t);

            void run(Report *report);
    };

}

#endif
