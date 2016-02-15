#include "test_vector.h"
#include "vector.h"

namespace bust::math {

    struct MathVectorScalarTestCase {
        std::string name;
        Vector v;
        void (*run)(testing::Test &t, MathVectorScalarTestCase &c);
    };

    MathVectorScalarTestCase math_vector_tests[] = {
       { "Get Dimensions",
          { (std::size_t) 5},
          [](testing::Test &t, MathVectorScalarTestCase &c) { 
              t.assertEqual("Vector size should have been 5", (unsigned) 5, (unsigned) c.v.getDimensions());
          }
       },
       { "Fields initialized to 0.0",
          { (std::size_t) 5},
          [](testing::Test &t, MathVectorScalarTestCase &c) { 
              for(std::size_t i = 0; i < c.v.getDimensions(); i++) {
                  t.assertEqual("Vector should be fully initialized to 0 by default", 0.0, c.v.get(i));
              }
           }
       },
       { "Fields should have been clear() to 5.0",
          { (std::size_t) 5},
          [](testing::Test &t, MathVectorScalarTestCase &c) { 
              c.v.clear(5.0);
              for(std::size_t i = 0; i < c.v.getDimensions(); i++) {
                  t.assertEqual("Vector should be set to 5.0 by clear()", 5.0, c.v.get(i));
              }
           }
       },
       { "Fields should be initialized by array",
          { (double[5]) { 0.0, -1.0, 1.0, -2.0, 3.0 }, (std::size_t) 5},
          [](testing::Test &t, MathVectorScalarTestCase &c) { 
              double a[5] = { 0.0, -1.0, 1.0, -2.0, 3.0 };
              for(std::size_t i = 0; i < c.v.getDimensions(); i++) {
                  t.assertEqual("Vector should be set to 5.0 by clear()", a[i], c.v.get(i));
              }
           }
       },
       { "vector translated by another vector",
          { (double[5]) { 1.0, 3.0, 5.0, 7.0, 9.0 }, (std::size_t) 5},
          [](testing::Test &t, MathVectorScalarTestCase &c) { 
              Vector x((double[5]) { 0.0, -1.0, 1.0, -2.0, 3.0 }, 5);
              Vector y((double[5]) { 1.0, 2.0, 6.0, 5.0, 12.0 }, 5);
              c.v.translate(x);
              for(std::size_t i = 0; i < c.v.getDimensions(); i++) {
                  t.assertEqual("Vector should be set to 5.0 by clear()", y.get(i), c.v.get(i));
              }
           }
       },
       { "vector scaled by a scalar",
          { (double[5]) { 10.0, 20.0, 50.0, 5.0, 15.0 }, (std::size_t) 5},
          [](testing::Test &t, MathVectorScalarTestCase &c) { 
              Vector y((double[5]){ 2.0, 4.0, 10.0, 1.0, 3.0 }, 5);
              c.v.scale(0.2);
              for(std::size_t i = 0; i < c.v.getDimensions(); i++) {
                  t.assertEqual("Vector should be set to 5.0 by clear()", y.get(i), c.v.get(i));
              }
           }
       },
       { "should throw vector_bounds_error on bad get",
          { (std::size_t) 5},
          [](testing::Test &t, MathVectorScalarTestCase &c) { 
              try {
                  c.v.get((std::size_t) 10); 
                  t.fail("Expected vector_bounds_error on Vector::get but execution continued");
              } catch (bust::math::VectorBoundsException &e) {
                  // we pass if we get here
              } catch (std::exception &e) {
                  t.fail("Expected vector_bounds_error on Vector::get but got other exception");
              }
           }
       },
       { "should throw vector_bounds_error on bad set",
          { (std::size_t) 5},
          [](testing::Test &t, MathVectorScalarTestCase &c) { 
              try {
                  c.v.set((std::size_t) 10, 5.0); 
                  t.fail("Expected vector_bounds_error on Vector::set but execution continued");
              } catch (bust::math::VectorBoundsException &e) {
                  // we pass if we get here
              } catch (std::exception &e) {
                  t.fail("Expected vector_bounds_error on Vector::set but got other exception");
              }
           }
       },
       { "length should match x axis",
          { (double[3]) { 13.0, 0, 0 }, (std::size_t) 3},
          [](testing::Test &t, MathVectorScalarTestCase &c) { 
              t.assertEqual("calculating length pointing x only", 13.0, c.v.getMagnitude());
          }
       },
       { "length should match z axis",
          { (double[3]) { 0.0, 0, 19.0 }, (std::size_t) 3},
          [](testing::Test &t, MathVectorScalarTestCase &c) { 
              t.assertEqual("calculating length pointing z only", 19.0, c.v.getMagnitude());
          }
       },
       { "distance along x axis",
          { (double[3]) { 20.0, 0, 0 }, (std::size_t) 3},
          [](testing::Test &t, MathVectorScalarTestCase &c) { 
              Vector w(c.v);
              w.scale(0.5);
              t.assertEqual("calculating distance along x only", 10.0, c.v.getDistance(w));
          }
       },
       { "distance along a few axis",
          { (double[3]) { 20.0, 5.0, 28 }, (std::size_t) 3},
          [](testing::Test &t, MathVectorScalarTestCase &c) { 
              Vector w(c.v);
              w.scale(0.5);
              t.assertEqual("calculating distance over multiple axis", c.v.getMagnitude()/2, c.v.getDistance(w), 1.0e-6);
          }
       },
       { "test scaleTo()",
          { (double[3]) { 5.0, 7.0, 11.0 }, (std::size_t) 3},
          [](testing::Test &t, MathVectorScalarTestCase &c) { 
              c.v.scaleTo(5.0);
              t.assertEqual("scale to should result in 5.0", 5.0, c.v.getMagnitude(), 1.0e-6);
          }
       },
    };

    void MathVectorTest::run() {

        for (MathVectorScalarTestCase t : math_vector_tests) {
            t.run(*this, t);
        }

    }

}

