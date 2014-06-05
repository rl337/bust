#include "test.h"

namespace jarvis_testing {

    Test::Test(std::string name) {
        name = name;
        status = None;
        mesg = "No Tests Executed";
    }


    TestStatus Test::getStatus() {
        return status;
    }

    void Test::error() {
        status = Error;
    }

    void Test::error(std::string mesg) {
        error();
        mesg = mesg;
    }

    void Test::fail() {
        status = Fail;
    }

    void Test::fail(std::string mesg) {
        fail();
        mesg = mesg;
    }

    void Test::abort() {
        status = Abort;
    }

    void Test::abort(std::string mesg) {
        abort();
        mesg = mesg;
    }

    void Test::skip() {
        status = Skipped;
    }

    void Test::skip(std::string mesg) {
        skip();
        mesg = mesg;
    }

    void Test::execute() {

        try {
            run();
            status = Pass;
        } catch (std::exception& e) {
            error(e.what());
        }
    }

}
