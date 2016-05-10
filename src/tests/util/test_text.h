#include "test.h"

namespace bust::util {

    class UtilTextTest : public bust::testing::Test {

        public:
            UtilTextTest() : testing::Test("UtilTextTest") {}

            void run();
            void init(){};
            void cleanup(){};
    };

}
