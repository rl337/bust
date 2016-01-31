#include "test.h"

namespace png {

    class PNGPNGTest : public testing::Test {

        public:
            PNGPNGTest() : testing::Test("PNGPNGTest") {}

            void run();
            void init(){};
            void cleanup(){};
    };

}
