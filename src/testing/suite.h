#include <string>
#include <vector>
#include "test.h"

namespace jarvis_testing {

    class Suite {
            std::vector<Test *> tests;
            std::string name;

        public:
            Suite(std::string name);
            void add(Test *t);

            void run();
    };

}
