#include "test_vector.h"
#include "vector.h"

namespace math {

    void MathVectorTest::run() {

        math::Vector *v = new math::Vector(5);


        this->assertEqual("Vector size should have been t", 5, (int) v->getSize());
    }

}

