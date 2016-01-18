#ifndef __JV_TEST_H__
#define __JV_TEST_H__

#include <string>
#include <iostream>
#include <sstream>
#include <exception>

namespace testing {

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

            void assertEqual(std::string mesg, int expected, int actual);
            void assertEqual(std::string mesg, unsigned expected, unsigned actual);
            void assertEqual(std::string mesg, long expected, long actual);
            void assertEqual(std::string mesg, unsigned long expected, unsigned long actual);
            void assertEqual(std::string mesg, double expected, double actual, double error);
            void assertEqual(std::string mesg, double expected, double actual);
            void assertEqual(std::string mesg, std::string expected, std::string actual);

            void assertNotEqual(std::string mesg, int expected, int actual);
            void assertNotEqual(std::string mesg, unsigned expected, unsigned actual);
            void assertNotEqual(std::string mesg, long expected, long actual);
            void assertNotEqual(std::string mesg, unsigned long expected, unsigned long actual);
            void assertNotEqual(std::string mesg, double expected, double actual, double error);
            void assertNotEqual(std::string mesg, double expected, double actual);
            void assertNotEqual(std::string mesg, std::string expected, std::string actual);

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
