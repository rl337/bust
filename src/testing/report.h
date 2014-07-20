#ifndef __JV_REPORT_H__
#define __JV_REPORT_H__

#include <string>
#include <vector>
#include "test.h"

namespace testing {

    class Report {

        public:
            virtual void report(Test *t) = 0;
    };

    class StdoutReport : public Report {
        public:
            void report(Test *t);
    };

}

#endif
