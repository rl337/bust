#include "png_suite.h"

#include "test_png.h"

namespace bust::png {

    PNGSuite::PNGSuite() : bust::testing::Suite("PNGSuite", true) {
        this->add(new PNGPNGTest());
    }
}
