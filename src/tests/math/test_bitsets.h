#include "test.h"

namespace math {

    class MathBitSetsTest : public testing::Test {

        public:
            MathBitSetsTest() : testing::Test("MathBitSetsTest") {}

            void run();
            void init(){};
            void cleanup(){};
    };

}
