#include "test_svg.h"

namespace svg {

    void SVGColorTest::run() {
        this->assertEqual("Colors should work", "blue", svg::colors::Blue.getName());
        this->assertEqual("Colors should work", "blue", svg::colors::Blue.getValue());

        svg::Color custom1("custom1", "#FF77EE");
        this->assertEqual("Colors should work", "custom1", custom1.getName());
        this->assertEqual("Colors should work", "#FF77EE", custom1.getValue());

        this->assertEqual("Styles should work", "default", svg::styles::Default.getName());
        this->assertEqual("Styles should work", "none", svg::styles::Default.getFill().getName());
        this->assertEqual("Styles should work", "black", svg::styles::Default.getStroke().getName());
    }

}

