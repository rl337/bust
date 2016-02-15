#include "test.h"

#include "style.h"
#include "color.h"
#include "svg.h"

namespace bust::svg {

    class SVGSVGTest : public bust::testing::Test {

        public:
            SVGSVGTest() : testing::Test("SVGSVGTest") {}

            void run();
            void init(){};
            void cleanup(){};
    };

}
