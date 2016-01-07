#include "test_svg.h"
#include <sstream>

namespace svg {

    void SVGSVGTest::run() {
        std::stringstream out;
        Rectangle r(1, 3, 5, 7);
        r.append(out);
        
        std::string s = out.str();
        this->assertEqual("Verify Rectangle", "<rect x=\"1\" y=\"3\" width=\"5\" height=\"7\" stroke=\"black\" stroke-width=\"2\"/>", s);
    }

}

