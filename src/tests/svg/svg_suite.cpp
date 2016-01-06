#include "svg_suite.h"

#include "test_color.h"
#include "test_svg.h"

namespace svg {

    SVGSuite::SVGSuite() : Suite("SVGSuite", true) {
        this->add(new SVGSVGTest());
        this->add(new SVGColorTest());
    }

}
