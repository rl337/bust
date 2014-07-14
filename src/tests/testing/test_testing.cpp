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

void TestingStatusTest::errorWithException() {
    throw new std::exception();
}

void TestingStatusTest::failWithAssertEqualString() {
    this->assertEqual("fail with assertEqual(String)", "foo", "bar");
}

void TestingStatusTest::failWithAssertEqualInt() {
    this->assertEqual("fail with assertEqual(Int)", 13, 42);
}

void TestingStatusTest::failWithAssertEqualLong() {
    this->assertEqual("fail with assertEqual(Long)", 13l, 42l);
}

void TestingStatusTest::failWithAssertEqualDouble() {
    this->assertEqual("fail with assertEqual(Double)", 13.00, 42.00);
}

void TestingStatusTest::failWithAssertNotEqualString() {
    this->assertEqual("fail with assertNotEqual(String)", "foo", "foo");
}

void TestingStatusTest::failWithAssertNotEqualInt() {
    this->assertEqual("fail with assertNotEqual(Int)", 13, 42);
}

void TestingStatusTest::failWithAssertNotEqualLong() {
    this->assertEqual("fail with assertNotEqual(Long)", 13l, 42l);
}

void TestingStatusTest::failWithAssertNotEqualDouble() {
    this->assertEqual("fail with assertNotEqual(Long)", 13.00, 42.00);
}

}
