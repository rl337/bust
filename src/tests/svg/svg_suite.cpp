#include "svg_suite.h"

#include "test_svg.h"

namespace bust::svg {

    SVGSuite::SVGSuite() : bust::testing::Suite("SVGSuite", true) {
        this->add(new SVGSVGTest());
    }

}
