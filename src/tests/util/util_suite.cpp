#include "util_suite.h"

#include "test_checksums.h"
#include "test_zlib.h"

namespace util {

    UtilSuite::UtilSuite() : Suite("UtilSuite", true) {
        this->add(new UtilChecksumsTest());
        this->add(new UtilZLibTest());
    }
}
