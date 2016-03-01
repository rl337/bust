
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

    template <typename T>
    std::string CircularArray<T>::to_string() {
        std::stringstream out;
        std::size_t size = this->data.size() - 1;
        for(std::size_t i = 0; i < size; i++) {
            out << this->data[i] << ',';
        }
        out << this->data[size];
        return out.str();
    }

    template <typename T>
    std::string CircularArray2D<T>::to_string() {
        std::stringstream out;
        for(std::size_t y = 0; y < this->height; y++) {
            for(std::size_t x = 0; x < this->width-1; x++) {
                out << this->get2D(x, y) << ',';
            }
            out << this->get2D(this->width-1, y) << std::endl;
        }
        out << std::endl;

        return out.str();
    }

    template class CircularArray<int>;
    template class CircularArray2D<int>;
}

