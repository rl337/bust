#include "test_svg.h"

namespace svg {

    void SVGColorTest::run() {
        this->assertEqual("Colors should work", "blue", svg::colors::Blue.getName());
        this->assertEqual("Colors should work", "blue", svg::colors::Blue.getValue());
    }

}

