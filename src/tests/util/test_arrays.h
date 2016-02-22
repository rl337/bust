#include "test.h"

#include "arrays.h"

namespace bust::util {

    class UtilArraysTest : public testing::Test {

        public:
            UtilArraysTest() : testing::Test("UtilArraysTest") {}

            void run();
            void init(){};
            void cleanup(){};
    };

}
