#include "test.h"

#include "style.h"
#include "color.h"

namespace bust::util {

    class UtilColorTest : public testing::Test {

        public:
            UtilColorTest() : testing::Test("UtilColorTest") {}

            void run();
            void init(){};
            void cleanup(){};
    };

}
