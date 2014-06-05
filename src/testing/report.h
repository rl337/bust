#include <string>
#include <vector>
#include "test.h"

namespace jarvis_testing {

    class Report {

        public:
            virtual void report(Test *t) = 0;
    };

}
