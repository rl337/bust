#include "test.h"

namespace jarvis_testing {

    Test::Test(std::string name) {
        Name = name;
        Status = None;
        Mesg = "No Tests Executed";
    }


    TestStatus Test::getStatus() {
        return Status;
    }

    void Test::init() {
    }

    void Test::cleanup() {
    }

    void Test::error() {
        Status = Error;
    }

    void Test::error(std::string mesg) {
        error();
        Mesg = mesg;
    }

    void Test::fail() {
        Status = Fail;
    }

    void Test::fail(std::string mesg) {
        fail();
        Mesg = mesg;
    }

    void Test::abort() {
        Status = Abort;
    }

    void Test::abort(std::string mesg) {
        abort();
        Mesg = mesg;
    }

    void Test::skip() {
        Status = Skipped;
    }

    void Test::skip(std::string mesg) {
        skip();
        Mesg = mesg;
    }
}
