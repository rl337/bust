#include "test_vector.h"
#include "vector.h"

namespace math {

    void MathVectorTest::run() {

        math::Vector v(5);
        int actual_size = (int) v.getDimensions();
        this->assertEqual("Vector size should have been t", 5, actual_size);

        for(std::size_t i = 0; i < actual_size; i++) {
            this->assertEqual("Vector should be fully initialized to 0 by default", 0.0, v.get(i));
        }
  
        v.clear(5.0);
        for(std::size_t i = 0; i < actual_size; i++) {
            this->assertEqual("Vector should have been cleared to 5.0", 5.0, v.get(i));
        }

        double a[5] = { 0.0, -1.0, 1.0, -2.0, 3.0 };
        math::Vector w(a, 5); 
        for(std::size_t i = 0; i < 5; i++) {
            this->assertEqual("Vector w should have expected values", a[i], w.get(i));
        }

        v.translate(w);
        for(std::size_t i = 0; i < 5; i++) {
            this->assertEqual("Vector v should now have v + w", a[i] + 5, v.get(i));
        }

        v.scale(0.25);
        for(std::size_t i = 0; i < 5; i++) {
            this->assertEqual("Vector v should now have v + w", (a[i] + 5) / 4, v.get(i));
        }

        try {
            v.get((std::size_t) 10); 
            this->fail("Expected vector_bounds_error on Vector::get but execution continued");
        } catch (math::VectorBoundsException &e) {
            // we pass if we get here
        } catch (std::exception &e) {
            this->fail("Expected vector_bounds_error on Vector::get but got other exception");
        }

        try {
            v.set((std::size_t) 10, 50.0); 
            this->fail("Expected vector_bounds_error on Vector::set but execution continued");
        } catch (math::VectorBoundsException &e) {
            // we pass if we get here
        } catch (std::exception &e) {
            this->fail("Expected vector_bounds_error on Vector::set but got other exception");
        }

    }

}

