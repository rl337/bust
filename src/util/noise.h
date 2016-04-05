#ifndef __JV_UTIL_NOISE_H__
#define __JV_UTIL_NOISE_H__

#include <cstdint>
#include <random>

namespace bust::util {

    class RandomSource {
        private:
            std::mt19937_64 source;
            std::uniform_real_distribution<double> distribution;
        
        public:
            RandomSource(int seed, double min=0.0, double max=1.0) : source(), distribution(min, max) { source.seed(seed); }
            
            double get() { return this->distribution(this->source); }
    };

}

#endif