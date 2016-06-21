
#include "noise.h"

namespace bust::util {

    template <typename T>
    UniformNoiseSurface<T>::UniformNoiseSurface(UniformRandomSource<T> &src, uint32_t w, uint32_t h, double xscale, double yscale) : NoiseSurface<T>(xscale, yscale), source(src), data(w, h, method_cosine) {
        for (uint32_t i = 0; i < w; i++) {
            for (uint32_t j = 0; j < h; j++) {
                T value = src.get();
                data.set_source(i, j, value);
            }
        }
    }

    template class UniformNoiseSurface<double>;
    template class UniformNoiseSurface<bust::util::Color>;
}
