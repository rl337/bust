#include "test.h"

namespace bust::png {

    class PNGPNGTest : public bust::testing::Test {

        public:
            PNGPNGTest() : bust::testing::Test("PNGPNGTest") {}

            void run();
            void init(){};
            void cleanup(){};
    };

}
