
#include "noise.h"

namespace bust::util {

    template <typename T>
    NoiseSurface<T>::NoiseSurface(UniformRandomSource<T> &src, uint32_t w, uint32_t h) : source(src), data(w, h, method_cosine) {
        for (uint32_t i = 0; i < w; i++) {
            for (uint32_t j = 0; j < h; j++) {
                double value = src.get();
                data.set_source(i, j, value);
            }
        }
    }

    template class NoiseSurface<double>;
}
