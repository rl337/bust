#include "test.h"

namespace math {

    class MathVectorTest : public testing::Test {

        public:
            MathVectorTest() : testing::Test("MathVectorTest") {}

            void run();
            void init(){};
            void cleanup(){};
    };

}
