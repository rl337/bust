#include "test.h"

namespace bust::math {

    class MathVectorTest : public bust::testing::Test {

        public:
            MathVectorTest() : bust::testing::Test("MathVectorTest") {}

            void run();
            void init(){};
            void cleanup(){};
    };

}
