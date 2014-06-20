#ifndef __REPORT_H__
#define __REPORT_H__

#include <string>
#include <vector>
#include "test.h"

namespace jarvis_testing {

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
