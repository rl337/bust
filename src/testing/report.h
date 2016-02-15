#ifndef __BUST_TESTING_REPORT_H__
#define __BUST_TESTING_REPORT_H__

#include <string>
#include <vector>

#include "test.h"
#include "suite.h"

namespace bust::testing {

    class Suite;

    class Report {

        public:
            virtual void report(Suite *s, Test *t) = 0;
    };

    class StdoutReport : public Report {
        public:
            void report(Suite *s, Test *t);
    };

    class MultiReport : public Report {
        private:
            std::vector<Report *> reports;
        public:
            void report(Suite *s, Test *t);
            void add(Report *r);
    };

}

#endif
