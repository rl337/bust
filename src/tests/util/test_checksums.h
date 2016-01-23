#include "test.h"

namespace util {

    class UtilChecksumsTest : public testing::Test {

        public:
            UtilChecksumsTest() : testing::Test("UtilChecksumsTest") {}

            void run();
            void init(){};
            void cleanup(){};
    };

}
