#include "test.h"

namespace bust::util {

    class UtilZLibTest : public bust::testing::Test {

        public:
            UtilZLibTest() : bust::testing::Test("UtilZLibTest") {}

            void run();
            void init(){};
            void cleanup(){};
    };

}
