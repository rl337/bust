#include "util_suite.h"

#include "test_checksums.h"
#include "test_zlib.h"
#include "test_color.h"
#include "test_arrays.h"

namespace bust::util {

    UtilSuite::UtilSuite() : Suite("UtilSuite", true) {
        this->add(new UtilChecksumsTest());
        this->add(new UtilZLibTest());
        this->add(new UtilColorTest());
        this->add(new UtilArraysTest());
    }
}
