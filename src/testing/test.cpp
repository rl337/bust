#include "test.h"

namespace jarvis_testing {
    const double default_error = 1.0e-80;

    Test::Test(std::string name) {
        this->name = name;
        this->status = None;
        this->mesg = "No Tests Executed";
    }


    TestStatus Test::getStatus() {
        return status;
    }

    std::string Test::getName() {
        return name;
    }

    std::string Test::getMessage() {
        return mesg;
    }

    void Test::error() {
        this->error("no message");
    }

    void Test::error(std::string mesg) {
        throw AssertionError(mesg);
    }

    void Test::fail() {
        this->fail("no message");
    }

    void Test::fail(std::string mesg) {
        throw AssertionFail(mesg);
    }

    void Test::abort() {
        this->abort("no message");
    }

    void Test::abort(std::string mesg) {
        throw AssertionAbort(mesg);
    }

    void Test::skip() {
        this->skip("no message");
    }

    void Test::skip(std::string mesg) {
        throw AssertionSkip(mesg);
    }

    template<typename X> std::string _message(std::string name, std::string mesg, X expected, X actual) {
        std::stringstream x;
        x << name << ": " << mesg << " Expected: " << expected << " Actual: " << actual;
        return x.str();
    }

    void Test::assertEqual(std::string mesg, int expected, int actual) {
        if (expected != actual) {
            throw AssertionFail(_message<int>(name, mesg, expected, actual));
        }
    }

    void Test::assertEqual(std::string mesg, long expected, long actual) {
        if (expected != actual) {
            throw AssertionFail(_message<long>(name, mesg, expected, actual));
        }
    }

    void Test::assertEqual(std::string mesg, double expected, double actual, double error) {
        float low = expected - error;
        float high = expected + error;
        if (actual < low || actual > high) {
            throw AssertionFail(_message<double>(name, mesg, expected, actual));
        }
    }

    void Test::assertEqual(std::string mesg, double expected, double actual) {
        this->assertEqual(mesg, expected, actual, default_error);
    }

    void Test::assertEqual(std::string mesg, std::string expected, std::string actual) {
        if (expected != actual) {
            throw AssertionFail(_message<std::string>(name, mesg, expected, actual));
        }
    }

    void Test::assertNotEqual(std::string mesg, int expected, int actual) {
        if (expected != actual) {
            throw AssertionFail(_message<int>(name, mesg, expected, actual));
        }
    }

    void Test::assertNotEqual(std::string mesg, long expected, long actual) {
        if (expected != actual) {
            throw AssertionFail(_message<long>(name, mesg, expected, actual));
        }
    }

    void Test::assertNotEqual(std::string mesg, double expected, double actual, double error) {
        float low = expected - error;
        float high = expected + error;
        if (actual >= low && actual <= high) {
            throw AssertionFail(_message<long>(name, mesg, expected, actual));
        }
    }

    void Test::assertNotEqual(std::string mesg, double expected, double actual) {
        this->assertNotEqual(mesg, expected, actual, default_error);
    }

    void Test::assertNotEqual(std::string mesg, std::string expected, std::string actual) {
    }

    void Test::execute() {

        try {
            run();
            status = Pass;
            this->mesg = "Pass";
        } catch (std::exception& e) {
            this->mesg = e.what();
            this->status = Abort;
        } catch (Assertion& a) {
            this->mesg = a.getMessage();
            this->status = a.getStatus();
        }
    }

    Assertion::Assertion(TestStatus status, std::string message) : status(status), message(message) {}

    TestStatus Assertion::getStatus() {
        return this->status;
    } 

    std::string Assertion::getMessage() {
        return this->message;
    }

    AssertionError::AssertionError(std::string message) : Assertion(Error, message) {}
    AssertionFail::AssertionFail(std::string message) : Assertion(Fail, message) {}
    AssertionSkip::AssertionSkip(std::string message) : Assertion(Skip, message) {}
    AssertionAbort::AssertionAbort(std::string message) : Assertion(Abort, message) {}
}

