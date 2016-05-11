
#include <iostream>
#include "noise.h"
#include "test_noise.h"

namespace bust::util {

    void UtilNoiseTest::run() {
        bust::util::DoubleRandomSource src(0, 0.0, 1.0);

        double sum = 0.0;
        double count = 1000000.0;
        for(double i = 0.0; i < count; i+=1.0) {
            sum += src.get();
        }
        double mean = sum / count;

        this->assertEqual("Value should be about 0.5", 0.5, mean, 0.01);

    }

}

