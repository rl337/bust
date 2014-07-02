#ifndef __JT_TEST_H__
#define __JT_TEST_H__

#include <string>
#include <exception>

namespace jarvis_testing {

    enum TestStatus { None, Pass, Fail, Error, Abort, Skip };

    class Test {
        private:
            TestStatus status;
            std::string name;
            std::string mesg;

        protected:
            virtual void run() = 0;

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

            void execute();

            virtual void init() = 0;
            virtual void cleanup() = 0;
            virtual ~Test() {};
    };

    class Assertion {
        private:
            TestStatus status;
            std::string message;

        protected:
            Assertion(TestStatus status, std::string message);

        public:
            TestStatus getStatus();
            std::string getMessage();
    };

    class AssertionError : public Assertion {
        public:
            AssertionError(std::string message);
    };

    class AssertionFail : public Assertion {
        public:
            AssertionFail(std::string message);
    };

    class AssertionSkip : public Assertion {
        public:
            AssertionSkip(std::string message);
    };

    class AssertionAbort : public Assertion {
        public:
            AssertionAbort(std::string message);
    };

}

#endif
