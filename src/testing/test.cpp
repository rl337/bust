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
        this->status = Error;
    }

    void Test::error(std::string mesg) {
        error();
        this->mesg = mesg;
    }

    void Test::fail() {
        this->status = Fail;
    }

    void Test::fail(std::string mesg) {
        fail();
        this->mesg = mesg;
    }

    void Test::abort() {
        this->status = Abort;
    }

    void Test::abort(std::string mesg) {
        abort();
        this->mesg = mesg;
    }

    void Test::skip() {
        this->status = Skip;
    }

    void Test::skip(std::string mesg) {
        skip();
        this->mesg = mesg;
    }

    void Test::execute() {

        try {
            run();
            status = Pass;
            this->mesg = "Pass";
        } catch (std::exception& e) {
            error(e.what());
        }
    }

}
