#include "test_color.h"

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

        
        svg::Color custom2("custom2", "#77FFEE");
        svg::Color custom1a(custom1);
        
        if ( custom1 == custom2 ) {
            this->fail("custom1 should not be the same as custom2");
        }

        if ( custom1 == custom1a ) {
            ; // expected behavior
        } else {
            this->fail("custom1 should be the same as custom1a");
        }

        if ( custom1 != custom2 ) {
           ;
        } else {
            this->fail("custom1 should not be the same as custom2");
        }

        if ( custom1 != custom1a ) {
            this->fail("custom1 should be the same as custom1a");
        }
    }


}

