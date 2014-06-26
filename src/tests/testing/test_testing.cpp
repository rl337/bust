#include "test_testing.h"

namespace jarvis_testing {

void TestingStatusTest::run() {

    TestingStatusTest *instance = new TestingStatusTest();

    std::string expectedMessage = "Tis an error quite bad";
    instance->error(expectedMessage);

    TestStatus actualStatus = instance->getStatus();
    if (actualStatus != Error) {
        error("Expected a status of Error");
    }

    std::string actualMessage = instance->getMessage();
    if (expectedMessage.compare(actualMessage) != 0) {
        error("Expected the correct message");
    }

    delete instance;

}

}
