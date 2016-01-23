#include "util_suite.h"

#include "test_checksums.h"

namespace util {

    UtilSuite::UtilSuite() : Suite("UtilSuite", true) {
        this->add(new UtilChecksumsTest());
    }
}
