
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

    template <typename SurfaceType, typename T>
    T LayeredNoiseSurface<SurfaceType, T>::get(double x, double y) {
        if (layers.size() < 1) {
            throw no_layers_surface_exception;
        }

        T final = layers[0].surface.get(x, y);
        for (int i = 1; i < layers.size(); i++) {
            LayerDefinition<SurfaceType> layer = layers[i];
            switch(layer.operation) {
                case Addition:
                    final = final + layer.surface.get(x, y);
                    break;
                case Subtraction:
                    final = final - layer.surface.get(x, y);
                    break;
            }
        }

        return final;
    }

#include <iostream>

    template <typename T>
    T CheckerSurface<T>::get(double x, double y) {
        double xprime = fmod(x, 2 * width);
        double yprime = fmod(y, 2 * height);

        if (xprime >= width) {
            if (yprime >= height) {
                return white;
            } else {
                return black;
            }
        } else {
            if (yprime >= height) {
                return black;
            } else {
                return white;
            }
        }
    }

    template class LayerDefinition<double>;
    template class CheckerSurface<double>;
    template class LayeredNoiseSurface<CheckerSurface<double>, double>;

    template class UniformNoiseSurface<double>;
    template class UniformNoiseSurface<bust::util::Color>;
}
