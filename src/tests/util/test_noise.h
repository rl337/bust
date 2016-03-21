#include "test.h"

namespace bust::util {

    class UtilNoiseTest : public bust::testing::Test {

        public:
            UtilNoiseTest() : bust::testing::Test("UtilNoiseTest") {}

            void run();
            void init(){};
            void cleanup(){};
    };

}
