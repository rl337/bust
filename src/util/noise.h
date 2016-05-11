#ifndef __JV_UTIL_NOISE_H__
#define __JV_UTIL_NOISE_H__

#include <cstdint>
#include <random>

namespace bust::util {

    template <typename T>
    class UniformRandomSource {
        protected:
            std::mt19937_64 source;
            std::uniform_real_distribution<double> distribution;
        
        public:
            UniformRandomSource(int seed, double min=0.0, double max=1.0) : source(), distribution(min, max) { source.seed(seed); }
            
            virtual T get() = 0;
    };

    class DoubleRandomSource : public UniformRandomSource<double> {

        public:
            DoubleRandomSource(int seed, double min=0.0, double max=1.0) : UniformRandomSource(seed, min, max) {};
            double get() { return this->distribution(this->source); }
    };


}

#endif
