#include "test.h"

namespace jarvis_testing {

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

