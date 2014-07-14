#include <iostream>
#include <cstdio>
#include "suite.h"
#include "test.h"

namespace jarvis_testing {

class TestingBaseTest : public Test {
    
    public:
        TestingBaseTest(std::string name) : Test(name) {};
        virtual void init() {};
        virtual void cleanup() {};
};


class TestingStatusTest : public TestingBaseTest {

    public:
        TestingStatusTest() : TestingBaseTest("TestingStatusTest") {};
    	virtual void run();
        virtual ~TestingStatusTest() {}

        void errorWithException();
        void failWithAssertEqualString();
        void failWithAssertEqualInt();
        void failWithAssertEqualLong();
        void failWithAssertEqualDouble();

        void failWithAssertNotEqualString();
        void failWithAssertNotEqualInt();
        void failWithAssertNotEqualLong();
        void failWithAssertNotEqualDouble();

};


}
