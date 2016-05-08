#include "test.h"

namespace bust::testing {
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

    std::string _messageLongHex(std::string name, std::string mesg, long expected, long actual) {
        std::stringstream x;
        x << name << ": " << mesg;
        x << " Expected: " << std::setw(8) << std::setfill('0') << std::hex << expected;
        x << " Actual: " << std::setw(8) << std::setfill('0') << std::hex << actual;

        return x.str();
    }

    std::string _firstlast(std::string x) {
        if (x.length() < 15) {
            return x;
        }

        std::stringstream result;
        result << x.substr(0, 5) << " ... " << x.substr(x.length() - 5, 5);
        return result.str(); 
    }

    template<typename X> std::string _messageStringHex(std::string name, std::string mesg, std::string expected, std::string actual) {
        std::stringstream x;

        char str[5];
        if (expected.length() != actual.length()) {
            x << name << ": " << mesg << " Length Mismatch. Expected: " << expected.length();
            x << " Actual: " << actual.length() << std::endl;
            x << " Literal Expected:" << std::endl;
            for (size_t i = 0; i < expected.length(); i++) {
                sprintf(str, "%02x",  (uint8_t) expected[i]);
                x << str << " "; 
            }
            x << std::endl;

            x << " Literal Actual:" << std::endl;
            for (size_t i = 0; i < actual.length(); i++) {
                sprintf(str, "%02x",  (uint8_t) expected[i]);
                x << str << " ";
            }
            x << std::endl;

            return x.str();
        }

        for (size_t i = 0; i < expected.length(); i++) {
            if (expected[i] != actual[i]) {
                x << name << ": " << mesg << " String Mismatch at position " << i << std::endl;
                x << " Actual: " << actual.length() << std::endl;
                x << " Literal Expected:" << std::endl;
                for (size_t j = 0; j < expected.length(); j++) {
                    sprintf(str, "%02x",  (uint8_t) expected[j]);
                    x << str << (i == j ? "]" : (i-1 == j ? "[" : " ")); 
                }
                x << std::endl;

                x << " Literal Actual:" << std::endl;
                for (size_t j = 0; j < actual.length(); j++) {
                    sprintf(str, "%02x",  (uint8_t) actual[j]);
                    x << str << (i == j ? "]" : (i-1 == j ? "[" : " ")); 
                }
                x << std::endl;
                break;
            }
        }

        return x.str();
    }

    void Test::assertEqual(std::string mesg, int expected, int actual) {
        if (expected != actual) {
            throw AssertionFail(_message<int>(name, mesg, expected, actual));
        }
    }

    void Test::assertEqual(std::string mesg, unsigned expected, unsigned actual) {
        if (expected != actual) {
            throw AssertionFail(_message<int>(name, mesg, expected, actual));
        }
    }

    void Test::assertEqual(std::string mesg, long expected, long actual) {
        if (expected != actual) {
            throw AssertionFail(_message<long>(name, mesg, expected, actual));
        }
    }

    void Test::assertEqual(std::string mesg, unsigned long expected, unsigned long actual) {
        if (expected != actual) {
            throw AssertionFail(_message<long>(name, mesg, expected, actual));
        }
    }

    void Test::assertEqualHex(std::string mesg, unsigned long expected, unsigned long actual) {
        if (expected != actual) {
            throw AssertionFail(_messageLongHex(name, mesg, expected, actual));
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

    void Test::assertEqualHex(std::string mesg, std::string expected, std::string actual) {
        if (expected != actual) {
            throw AssertionFail(_messageStringHex<std::string>(name, mesg, expected, actual));
        }
    }

    void Test::assertNotEqual(std::string mesg, int expected, int actual) {
        if (expected == actual) {
            throw AssertionFail(_message<int>(name, mesg, expected, actual));
        }
    }

    void Test::assertNotEqual(std::string mesg, unsigned expected, unsigned actual) {
        if (expected == actual) {
            throw AssertionFail(_message<int>(name, mesg, expected, actual));
        }
    }

    void Test::assertNotEqual(std::string mesg, long expected, long actual) {
        if (expected == actual) {
            throw AssertionFail(_message<long>(name, mesg, expected, actual));
        }
    }

    void Test::assertNotEqual(std::string mesg, unsigned long expected, unsigned long actual) {
        if (expected == actual) {
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
        if (expected == actual) {
            throw AssertionFail(_message<std::string>(name, mesg, expected, actual));
        }
    }

    void Test::execute() {

        try {
            run();
            status = Pass;
            this->mesg = "Pass";
        } catch (std::exception& e) {
            this->mesg = e.what();
            this->status = Error;
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

