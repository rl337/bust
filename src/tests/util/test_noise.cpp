
#include <iostream>
#include "noise.h"
#include "test_noise.h"

namespace bust::util {

    class TestDoubleNoiseSurface : public UniformNoiseSurface<double> {
        public:
            TestDoubleNoiseSurface(UniformRandomSource<double> src) : UniformNoiseSurface<double>(src, 1024, 1024) {}
    };

    template <typename ValueType>
    struct ExpectedValue {
        double x;
        double y;

        ValueType expected;
    };

    template <typename SurfaceType, typename ValueType>
    struct UtilNoiseSurfaceTestData {
        std::string name;

        SurfaceType surface;
        ValueType (*get)(SurfaceType &surface, double x, double y);
        std::vector<ExpectedValue<ValueType>> expected;

        void run(bust::testing::Test *t) {
            for (std::size_t i = 0; i < this->expected.size(); i++) {
                ExpectedValue<ValueType> expected = this->expected[i];

                ValueType actual = this->get(this->surface, expected.x, expected.y);

                t->assertEqual(this->name, expected.expected, actual);
            }
        }
    };
    
    UtilNoiseSurfaceTestData<LayeredNoiseSurface<CheckerSurface<double>, double>, double> util_noisesurface_tests[] = {
        { "Test Checker Surface",
            LayeredNoiseSurface<CheckerSurface<double>, double>(
                1.0, 1.0, {
                    { Addition, {1.0, 1.0, 5.0, 5.0, 0.0, 1.0} },
                }
            ),
            [](LayeredNoiseSurface<CheckerSurface<double>, double> &surface, double x, double y) { return surface.get(x, y); },
            {
                { 0.0,  0.0,  1.0},
                { 0.0,  5.0,  0.0},
                { 0.0, 10.0,  1.0},
                { 5.0,  0.0,  0.0},
                {10.0,  0.0,  1.0},
            },
        },
        { "Test Checker Surface",
            LayeredNoiseSurface<CheckerSurface<double>, double>(
                1.0, 1.0, {
                    { Addition,    {1.0, 1.0, 5.0, 5.0, 0.0, 1.0} },
                    { Subtraction, {1.0, 1.0, 2.5, 2.5, 0.0, 0.5} },
                }
            ),
            [](LayeredNoiseSurface<CheckerSurface<double>, double> &surface, double x, double y) { return surface.get(x, y); },
            {
                { 0.0,  0.0,  0.5}, // Both layers should be "white"
                { 0.0,  2.5,  1.0}, // Layer 1 is "white", layer 2 is "black"
                { 0.0,  7.5,  0.0}, // Layer 1 is "black", layer 2 is "black"
                { 2.5,  0.0,  1.0}, // Layer 1 is "white", layer 2 is "black"
                { 7.5,  0.0,  0.0}, // Layer 1 is "black", layer 2 is "black"
            },
        },
    };

    void test_uniform_random_src(bust::testing::Test *t) {
        UniformRandomSource<double> src(0, 0.0, 1.0);

        double sum = 0.0;
        double count = 1000000.0;
        for(double i = 0.0; i < count; i+=1.0) {
            sum += src.get();
        }
        double mean = sum / count;

        t->assertEqual("Value should be about 0.5", 0.5, mean, 0.01);
    }

    void test_noise_surface(bust::testing::Test *t) {
        UniformRandomSource<double> src(0, 0.0, 1.0);
        TestDoubleNoiseSurface surface(src);
        double sum2 = 0.0;
        double xlimit = 1000.0;
        double ylimit = 1000.0;
        for(double x = 0.0; x < xlimit; x+=1.0) {
            for(double y = 0.0; y < ylimit; y+=1.0) {
                sum2 += surface.get(x, y);
            }
        }
        double mean2 = sum2 / (xlimit * ylimit);
   
        t->assertEqual("Value should be about 0.5", 0.5, mean2, 0.01);
    }

    void UtilNoiseTest::run() {

        test_uniform_random_src(this);

        for (UtilNoiseSurfaceTestData<LayeredNoiseSurface<CheckerSurface<double>, double>, double> test : util_noisesurface_tests) {
            test.run(this);
        }

    }


}

