
#include <iostream>
#include "noise.h"
#include "test_noise.h"

namespace bust::util {

    class TestDoubleNoiseSurface : public UniformNoiseSurface<double> {

        public:
            TestDoubleNoiseSurface(UniformRandomSource<double> src) : UniformNoiseSurface<double>(src, 1024, 1024) {}
    };

    void UtilNoiseTest::run() {
        UniformRandomSource<double> src(0, 0.0, 1.0);

        double sum = 0.0;
        double count = 1000000.0;
        for(double i = 0.0; i < count; i+=1.0) {
            sum += src.get();
        }
        double mean = sum / count;

        this->assertEqual("Value should be about 0.5", 0.5, mean, 0.01);

        TestDoubleNoiseSurface surface(src);

        double sum2 = 0.0;
        double count2 = 1000000.0;
        for(double j = 0.0; j < count; j+=1.0) {
            sum2 += src.get();
        }
        double mean2 = sum2 / count2;
   
        this->assertEqual("Value should be about 0.5", 0.5, mean2, 0.01);
    }


}

