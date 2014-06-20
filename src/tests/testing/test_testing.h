#include <iostream>
#include "suite.h"
#include "test.h"

namespace jarvis_testing {

class TestingBaseTest : public Test {
    protected:
        Test *instance;
    
    public:
        TestingBaseTest(std::string name) : Test(name) {};
        void init();
        void cleanup();
};


class TestingStatusTest : public TestingBaseTest {
    public:
        TestingStatusTest() : TestingBaseTest("TestingStatusTest") {};
    	void run();
};


}
