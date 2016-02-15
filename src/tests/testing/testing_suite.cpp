#include "testing_suite.h"

#include "test_testing.h"

namespace bust::testing {

    TestingSuite::TestingSuite() : bust::testing::Suite("TestingSuite", true) {
        this->add(new TestingStatusTest());
    }

}
