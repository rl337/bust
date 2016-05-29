#ifndef __JV_UTIL_NOISE_H__
#define __JV_UTIL_NOISE_H__

#include <cstdint>
#include <random>

#include "arrays.h"

namespace bust::util {

    template <typename T>
    class UniformRandomSource {
        public:
            virtual T get() = 0;
    };

    template <>
    class UniformRandomSource<double> {
        private:
            std::mt19937_64 source;
            std::uniform_real_distribution<double> distribution;

        public:
            UniformRandomSource(int seed, double min=0.0, double max=1.0) {}
            double get() { return this->distribution(this->source); }
    };

    template <typename T>
    class NoiseSurface {
        private:
            UniformRandomSource<T> source;
            InterpolatedCircularArray2D<T> data;
    
        protected:
            NoiseSurface(UniformRandomSource<T> &src, uint32_t w, uint32_t h);

        public:
            T get(double x, double y) { return this->data.get(x, y); }
    };

    

}

#endif
