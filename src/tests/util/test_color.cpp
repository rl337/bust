#include "test_color.h"

namespace util {

    void UtilColorTest::run() {
        this->assertEqual("Colors should work", "blue", colors::Blue.getName());
        this->assertEqual("Colors should work", (unsigned long) 0x0000FFFF, (unsigned long) colors::Blue.getValue());

        Color custom1("custom1", 0xFF77EE);
        this->assertEqual("Colors should work", "custom1", custom1.getName());
        this->assertEqual("Colors should work", (unsigned long) 0xFF77EE, (unsigned long) custom1.getValue());

        Color custom2("custom2", 0x77FFEE);
        Color custom1a(custom1);
        
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

