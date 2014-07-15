#include "test_testing.h"

namespace jarvis_testing {


void TestingStatusTest::run() {

    TestingTestTest *instance = new TestingTestTest("test");
    instance->setAction(
        [](TestingTestTest *t) -> void {
            t->errorWithException();
        }
    );

    instance->execute();

    TestStatus actualStatus = instance->getStatus();
    if (actualStatus != Abort) {
        fail("Expected a status of Error");
    }

    delete instance;

}

void TestingTestTest::setAction(void (*action)(TestingTestTest *t)) {
    this->action = action;
}

void TestingTestTest::run() {
    void (*action)(TestingTestTest *t) = this->action;
    (*action)(this);
}

void TestingTestTest::errorWithException() {
    throw std::exception();
}

void TestingTestTest::failWithAssertEqualString() {
    this->assertEqual("fail with assertEqual(String)", "foo", "bar");
}

void TestingTestTest::failWithAssertEqualInt() {
    this->assertEqual("fail with assertEqual(Int)", 13, 42);
}

void TestingTestTest::failWithAssertEqualLong() {
    this->assertEqual("fail with assertEqual(Long)", 13l, 42l);
}

void TestingTestTest::failWithAssertEqualDouble() {
    this->assertEqual("fail with assertEqual(Double)", 13.00, 42.00);
}

void TestingTestTest::failWithAssertNotEqualString() {
    this->assertEqual("fail with assertNotEqual(String)", "foo", "foo");
}

void TestingTestTest::failWithAssertNotEqualInt() {
    this->assertEqual("fail with assertNotEqual(Int)", 13, 42);
}

void TestingTestTest::failWithAssertNotEqualLong() {
    this->assertEqual("fail with assertNotEqual(Long)", 13l, 42l);
}

void TestingTestTest::failWithAssertNotEqualDouble() {
    this->assertEqual("fail with assertNotEqual(Long)", 13.00, 42.00);
}

}
