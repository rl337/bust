
#include "noise.h"

namespace bust::util {

    template <typename T>
    NoiseSurface<T>::NoiseSurface(UniformRandomSource<T> &src, uint32_t w, uint32_t h, double scale) : source(src), data(w, h, method_cosine), scale(scale) {
        for (uint32_t i = 0; i < w; i++) {
            for (uint32_t j = 0; j < h; j++) {
                T value = src.get();
                data.set_source(i, j, value);
            }
        }
    }

    template class NoiseSurface<double>;
    template class NoiseSurface<bust::util::Color>;
}
