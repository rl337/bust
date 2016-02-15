#ifndef __BUST_TESTING_SUITE_H__
#define __BUST_TESTING_SUITE_H__

#include <string>
#include <vector>

#include "test.h"
#include "report.h"

namespace bust::testing {

    class Report;

    class Suite {
        private:
            std::vector<Test *> tests;
            std::string name;
            bool autodelete;

        public:
            Suite(std::string name);
            Suite(std::string name, bool autodelete);
            ~Suite();

            void add(Test *t);

            inline std::string getName() { return this->name; }

            void run(Report *report);
    };

}

#endif
