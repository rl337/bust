#include "svg_suite.h"

#include "test_svg.h"

namespace svg {

    SVGSuite::SVGSuite() : Suite("SVGSuite", true) {
        this->add(new SVGSVGTest());
    }

}
