#include "test.h"

namespace math {

    class MathChecksumsTest : public testing::Test {

        public:
            MathChecksumsTest() : testing::Test("MathChecksumsTest") {}

            void run();
            void init(){};
            void cleanup(){};
    };

}
