#include <string>

namespace jarvis_testing {

    enum TestStatus { None, Pass, Fail, Error, Abort, Skipped };

    class Test {
            TestStatus Status;
            std::string Name;
            std::string Mesg;

        public:
            Test(std::string name);

            void init();
            void cleanup();

            void fail();
            void fail(std::string mesg);

            void error();
            void error(std::string mesg);

            void abort();
            void abort(std::string mesg);

            void skip();
            void skip(std::string mesg);

            TestStatus getStatus();
    };

}
