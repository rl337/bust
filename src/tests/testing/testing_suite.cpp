#include "testing_suite.h"

#include "test_testing.h"

namespace testing {

    TestingSuite::TestingSuite() : Suite("TestingSuite", true) {
        this->add(new TestingStatusTest());
    }

}
