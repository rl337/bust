#include "math_suite.h"

#include "test_bitsets.h"
#include "test_vector.h"

namespace math {

    MathSuite::MathSuite() : Suite("MathSuite", true) {
        this->add(new MathBitSetsTest());
        this->add(new MathVectorTest());
    }
}
