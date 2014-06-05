#ifndef __JT_TEST_H__
#define __JT_TEST_H__

#include <string>
#include <exception>

namespace jarvis_testing {

    enum TestStatus { None, Pass, Fail, Error, Abort, Skip };

    class Test {
            TestStatus status;
            std::string name;
            std::string mesg;

            void execute();

        public:
            Test(std::string name);

            void fail();
            void fail(std::string mesg);

            void error();
            void error(std::string mesg);

            void abort();
            void abort(std::string mesg);

            void skip();
            void skip(std::string mesg);

            TestStatus getStatus();
            std::string getName();
            std::string getMessage();

            virtual void run() = 0;
            virtual void init() = 0;
            virtual void cleanup() = 0;
    };

}

#endif
