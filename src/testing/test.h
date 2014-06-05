#include <string>
#include <exception>

namespace jarvis_testing {

    enum TestStatus { None, Pass, Fail, Error, Abort, Skipped };

    class Test {
            TestStatus status;
            std::string name;
            std::string mesg;

            void execute();

        public:
            Test(std::string name);

            void fail();
            void fail(std::string mesg);

            void error();
            void error(std::string mesg);

            void abort();
            void abort(std::string mesg);

            void skip();
            void skip(std::string mesg);

            TestStatus getStatus();

            virtual void run() = 0;
            virtual void init() = 0;
            virtual void cleanup() = 0;
    };

}
