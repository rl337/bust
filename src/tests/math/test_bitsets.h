#include "test.h"
#include "bitsets.h"

namespace bust::math {

    class MathBitSetsTest : public bust::testing::Test {

        public:
            MathBitSetsTest() : bust::testing::Test("MathBitSetsTest") {}

            void run();
            void init(){};
            void cleanup(){};
    };

}
