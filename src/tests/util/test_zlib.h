#include "test.h"

namespace util {

    class UtilZLibTest : public testing::Test {

        public:
            UtilZLibTest() : testing::Test("UtilZLibTest") {}

            void run();
            void init(){};
            void cleanup(){};
    };

}
