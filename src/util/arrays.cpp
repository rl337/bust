
#include "arrays.h"

namespace bust::util {

    template <typename T>
    CircularArray<T>::CircularArray(std::size_t len) : length(len), data(std::vector<T>(len)) {
    }

    template <typename T>
    CircularArray<T>::CircularArray(const T raw[], std::size_t len) : length(len), data(std::vector<T>(len)) {
        for(std::size_t i = 0; i < len; i++) {
            this->data[i] = raw[i];
        }
    }

    template <typename T>
    CircularArray<T>::CircularArray(T raw[], std::size_t len) : length(len), data(std::vector<T>(len)) {
        for(std::size_t i = 0; i < len; i++) {
            this->data[i] = raw[i];
        }
    }

    template <typename T>
    CircularArray<T>::CircularArray(const CircularArray<T>& ca) : CircularArray(ca.length) {
        for(std::size_t i = 0; i < ca.data.size(); i++) {
            this->data[i] = ca.data[i];
        }
    }

    template class CircularArray<int>;
}

