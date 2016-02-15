#include "test.h"

namespace bust::util {

    class UtilChecksumsTest : public bust::testing::Test {

        public:
            UtilChecksumsTest() : bust::testing::Test("UtilChecksumsTest") {}

            void run();
            void init(){};
            void cleanup(){};
    };

}
