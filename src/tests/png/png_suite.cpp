#include "png_suite.h"

#include "test_png.h"

namespace png {

    PNGSuite::PNGSuite() : Suite("PNGSuite", true) {
        this->add(new PNGPNGTest());
    }
}
