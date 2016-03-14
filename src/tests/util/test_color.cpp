#include "test_color.h"

namespace bust::util {

    struct UtilColorTestCase {
        std::string name;
        Color (*test)(testing::Test &t, UtilColorTestCase &c);
        Color expected;

        void run(UtilColorTest &t) {
            Color actual = this->test(t, *this);
            t.assertEqualHex(this->name, this->expected.getValue(), actual.getValue());
        }
    };

    UtilColorTestCase util_color_tests[] = {
        { "simple color multiply", 
          [](testing::Test &t, UtilColorTestCase &c) {
              return Color("TestColor1", 0x102030FF) * 2;
          },
          Color("TestColor1", 0x204060FF)
        },
        { "simple color add", 
          [](testing::Test &t, UtilColorTestCase &c) {
              return Color("TestColor1", 0x102030FF) + Color("TestColor2", 0x102030FF);
          },
          Color("TestColor1", 0x204060FF)
        }
    };

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

        for (UtilColorTestCase t : util_color_tests) {
            t.run(*this);
        }


    }


}

