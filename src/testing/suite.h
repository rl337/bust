#include <string>
#include <vector>
#include "test.h"
#include "report.h"

namespace jarvis_testing {

    class Suite {
            std::vector<Test *> tests;
            std::vector<Report *> reports;
            std::string name;

        public:
            Suite(std::string name);
            void add(Test *t);
            void add(Report *t);

            void run();
    };

}
