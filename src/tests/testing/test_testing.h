#include <iostream>
#include <cstdio>
#include "suite.h"
#include "test.h"

namespace bust::testing {

class TestingStatusTest : public bust::testing::Test {
    
    public:
        TestingStatusTest() : bust::testing::Test("TestingStatusTest") {};
        void init() {};
        void run();
        void cleanup() {};
};


class TestingTestTest : public bust::testing::Test {
    private:
        void (*action)(TestingTestTest *t);

    public:
        void setAction(void (*x)(TestingTestTest *t));
    	// virtual void run();
        TestingTestTest(std::string name) : Test(name) {};
        // virtual ~TestingStatusTest() {}

        void init() {};
        void run();
        void cleanup() {};

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
