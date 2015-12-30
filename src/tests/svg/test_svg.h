#include "test.h"
#include "color.h"

namespace svg {

    class SVGColorTest : public testing::Test {

        public:
            SVGColorTest() : testing::Test("SVGColorTest") {}

            void run();
            void init(){};
            void cleanup(){};
    };

}
