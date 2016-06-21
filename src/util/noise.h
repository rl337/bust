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
            double xscale;
            double yscale;
    
        protected:
            NoiseSurface(double xscale, double yscale) : xscale(xscale), yscale(yscale) { }
            NoiseSurface() : NoiseSurface(1.0, 1.0) { }

        public:
            double get_xscale() { return xscale; }
            double get_yscale() { return yscale; }
            virtual T get(double x, double y) = 0;
    };

    template <typename T>
    class UniformNoiseSurface : public NoiseSurface<T> {
        private:
            UniformRandomSource<T> source;
            InterpolatedCircularArray2D<T> data;
    
        protected:
            UniformNoiseSurface(UniformRandomSource<T> &src, uint32_t w, uint32_t h, double xscale, double yscale);
            UniformNoiseSurface(UniformRandomSource<T> &src, uint32_t w, uint32_t h) : UniformNoiseSurface(src, w, h, 1.0, 1.0) {}

        public:
            virtual T get(double x, double y) { return this->data.get(x * this->get_xscale(), y * this->get_yscale()); }
    };

    template <typename T>
    class HighResUniformNoiseSurface : public UniformNoiseSurface<T>{
        public:
            HighResUniformNoiseSurface(UniformRandomSource<T> &src, double xscale, double yscale) : UniformNoiseSurface<T>(src, 1024, 1024, xscale, yscale) {}
            HighResUniformNoiseSurface(UniformRandomSource<T> &src, double scale) : UniformNoiseSurface<T>(src, 1024, 1024, scale, scale) {}
            HighResUniformNoiseSurface(UniformRandomSource<T> &src) : HighResUniformNoiseSurface(src, 1.0) {}

    };

    template <typename T>
    class MediumResUniformNoiseSurface : public UniformNoiseSurface<T>{
        public:
            MediumResUniformNoiseSurface(UniformRandomSource<T> &src, double xscale, double yscale) : UniformNoiseSurface<T>(src, 256, 256, xscale, yscale) {}
            MediumResUniformNoiseSurface(UniformRandomSource<T> &src, double scale) : UniformNoiseSurface<T>(src, 256, 256, scale, scale) {}
            MediumResUniformNoiseSurface(UniformRandomSource<T> &src) : MediumResUniformNoiseSurface(src, 1.0) {}

    };

    template <typename T>
    class LowResUniformNoiseSurface : public UniformNoiseSurface<T>{
        public:
            LowResUniformNoiseSurface(UniformRandomSource<T> &src, double xscale, double yscale) : UniformNoiseSurface<T>(src, 64, 64, xscale, yscale) {}
            LowResUniformNoiseSurface(UniformRandomSource<T> &src, double scale) : UniformNoiseSurface<T>(src, 64, 64, scale, scale) {}
            LowResUniformNoiseSurface(UniformRandomSource<T> &src) : LowResUniformNoiseSurface<T>(src, 1.0) {}

    };

}

#endif
