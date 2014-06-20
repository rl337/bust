#include "test_testing.h"

namespace jarvis_testing {

void TestingBaseTest::init() {
    instance = new TestingBaseTest();
}

void TestingBaseTest::cleanup() {
    delete instance;
}

void TestingBaseTest::run() {
    std::string expectedMessage = "Tis an error quite bad";
    instance->error(expectedMessage);

    TestStatus actualStatus = instance->getStatus();
    if (actual != Error) {
        error("Expected a status of " << Error << " but was " << actualStatus);
    }

    std::string actualMessage = instance.getMessage();
    if (expectedMessage.compare(actualMessage) != 0) {
        error("Expected a Message of " << expectedMessage << " but was " << actualMessage);
    }

}

}
