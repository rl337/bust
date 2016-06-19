#ifndef __JV_UTIL_NOISE_H__
#define __JV_UTIL_NOISE_H__

#include <cstdint>
#include <random>

#include "arrays.h"
#include "color.h"

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

    template <>
    class UniformRandomSource<Color> {
        private:
            std::mt19937_64 source;
            std::uniform_int_distribution<uint8_t> distribution;

        public:
            UniformRandomSource(int seed) {}
            Color get() {
                return Color(
                    this->distribution(this->source),
                    this->distribution(this->source),
                    this->distribution(this->source)
                );
            }
    };

    template <typename T>
    class NoiseSurface {
        private:
            UniformRandomSource<T> source;
            InterpolatedCircularArray2D<T> data;
            double scale;
    
        protected:
            NoiseSurface(UniformRandomSource<T> &src, uint32_t w, uint32_t h, double scale);
            NoiseSurface(UniformRandomSource<T> &src, uint32_t w, uint32_t h) : NoiseSurface(src, w, h, 1.0) {}

        public:
            T get(double x, double y) { return this->data.get(x * scale, y * scale); }
    };

    template <typename T>
    class HighResNoiseSurface : public NoiseSurface<T>{
        public:
            HighResNoiseSurface(UniformRandomSource<T> &src, double scale) : NoiseSurface<T>(src, 1024, 1024, scale) {}
            HighResNoiseSurface(UniformRandomSource<T> &src) : HighResNoiseSurface(src, 1.0) {}

    };

    template <typename T>
    class MediumResNoiseSurface : public NoiseSurface<T>{
        public:
            MediumResNoiseSurface(UniformRandomSource<T> &src, double scale) : NoiseSurface<T>(src, 256, 256, scale) {}
            MediumResNoiseSurface(UniformRandomSource<T> &src) : MediumResNoiseSurface(src, 1.0) {}

    };

    template <typename T>
    class LowResNoiseSurface : public NoiseSurface<T>{
        public:
            LowResNoiseSurface(UniformRandomSource<T> &src, double scale) : NoiseSurface<T>(src, 64, 64, scale) {}
            LowResNoiseSurface(UniformRandomSource<T> &src) : LowResNoiseSurface<T>(src, 1.0) {}

    };
}

#endif
