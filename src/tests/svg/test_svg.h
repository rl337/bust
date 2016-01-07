#include "test.h"

#include "style.h"
#include "color.h"
#include "svg.h"

namespace svg {

    class SVGSVGTest : public testing::Test {

        public:
            SVGSVGTest() : testing::Test("SVGSVGTest") {}

            void run();
            void init(){};
            void cleanup(){};
    };

}
