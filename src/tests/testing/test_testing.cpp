#include "test_testing.h"

namespace bust::testing {

typedef struct {
   std::string name;
   void (*action)(TestingTestTest *t);
   TestStatus expected;
} testcase;

testcase cases[] = {
    { "Error via Exception", 
       [](TestingTestTest *t) -> void {
           throw std::exception();
       },
       Abort
    },

    { "Fail with string assert equal", 
       [](TestingTestTest *t) -> void {
           t->assertEqual("fail with assertEqual(String)", "foo", "bar");
       },
       Fail
    },

    { "Pass with string assert equal", 
       [](TestingTestTest *t) -> void {
           t->assertEqual("pass with assertEqual(String)", "foo", "foo");
       },
       Pass
    },

    { "Fail with int assert equal", 
       [](TestingTestTest *t) -> void {
           t->assertEqual("fail with assertEqual(Int)", 13, 42);
       },
       Fail
    },

    { "Pass with int assert equal", 
       [](TestingTestTest *t) -> void {
           t->assertEqual("pass with assertEqual(Int)", 13, 13);
       },
       Pass
    },

    { "Fail with long assert equal", 
       [](TestingTestTest *t) -> void {
           t->assertEqual("fail with assertEqual(Long)", 13l, 42l);
       },
       Fail
    },

    { "Pass with long assert equal", 
       [](TestingTestTest *t) -> void {
           t->assertEqual("pass with assertEqual(Long)", 13l, 13l);
       },
       Pass
    },

    { "Fail with double assert equal", 
       [](TestingTestTest *t) -> void {
           t->assertEqual("fail with assertEqual(Double)", 13.00, 42.00);
       },
       Fail
    },

    { "Pass with double assert equal", 
       [](TestingTestTest *t) -> void {
           t->assertEqual("pass with assertEqual(Double)", 13.00, 13.00);
       },
       Pass
    },

    { "Fail with string assert not equal", 
       [](TestingTestTest *t) -> void {
           t->assertNotEqual("fail with assertNotEqual(String)", "foo", "foo");
       },
       Fail
    },

    { "Pass with string assert not equal", 
       [](TestingTestTest *t) -> void {
           t->assertNotEqual("pass with assertNotEqual(String)", "foo", "bar");
       },
       Pass
    },

    { "Fail with int assert not equal", 
       [](TestingTestTest *t) -> void {
           t->assertNotEqual("fail with assertNotEqual(Int)", 13, 13);
       },
       Fail
    },

    { "Pass with int assert not equal", 
       [](TestingTestTest *t) -> void {
           t->assertNotEqual("pass with assertNotEqual(Int)", 13, 42);
       },
       Pass
    },

    { "Fail with long assert not equal", 
       [](TestingTestTest *t) -> void {
           t->assertNotEqual("fail with assertNotEqual(Long)", 13l, 13l);
       },
       Fail
    },

    { "Pass with long assert not equal", 
       [](TestingTestTest *t) -> void {
           t->assertNotEqual("pass with assertNotEqual(Long)", 13l, 42l);
       },
       Pass
    },

    { "Fail with double assert not equal", 
       [](TestingTestTest *t) -> void {
           t->assertNotEqual("fail with assertNotEqual(Double)", 13.00, 13.00);
       },
       Fail
    },

    { "Pass with double assert not equal", 
       [](TestingTestTest *t) -> void {
           t->assertNotEqual("pass with assertNotEqual(Double)", 13.00, 42.00);
       },
       Pass
    },
};

void TestingStatusTest::run() {

    for(testcase thiscase : cases) {
        TestingTestTest *instance = new TestingTestTest("test");
        instance->setAction(thiscase.action);
        instance->execute();

        TestStatus actualStatus = instance->getStatus();
        if (actualStatus != thiscase.expected) {
            fail(thiscase.name + ": unexpected status");
        }

        delete instance;
    }

}

void TestingTestTest::setAction(void (*action)(TestingTestTest *t)) {
    this->action = action;
}

void TestingTestTest::run() {
    void (*action)(TestingTestTest *t) = this->action;
    (*action)(this);
}

}
