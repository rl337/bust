#ifndef __BUST_ARRAYS_H__
#define __BUST_ARRAYS_H__

#include <vector>
#include <sstream>
#include <cmath>
#include <cassert>

namespace bust::util {

    template <typename T>
    class CircularArray {
        private:
            std::size_t length;
            std::vector<T> data;

        public:
            CircularArray(std::size_t len=16);
            CircularArray(const CircularArray<T>& ca);
            CircularArray(const T arr[], std::size_t len=16);
            CircularArray(T arr[], std::size_t len=16);
            CircularArray(std::vector<T> arr);

            ~CircularArray() { }
            uint32_t size() { return this->length; }

            T& get(std::size_t i) { return this->data[i % this->length]; }
            T& operator[](std::size_t i) { return this->get(i); }

            std::string to_string();
    };

    template <typename T>
    class CircularArray2D : public CircularArray<T> {
        private:
            std::size_t width;
            std::size_t height;
            
        public:
            CircularArray2D(std::size_t width = 16, std::size_t height = 16) : CircularArray<T>(width * height), width(width), height(height) { }
            CircularArray2D(const T arr[], std::size_t width, std::size_t height) : CircularArray<T>(arr, width * height), width(width), height(height) { }
            CircularArray2D(std::vector<T> arr, std::size_t width, std::size_t height) : CircularArray<T>(arr), width(width), height(height) { assert(arr.size() == width * height); }

            T& get2D(std::size_t x, std::size_t y) { return this->get((y % this->height) * this->width + (x % this->width)); }
            std::size_t get_width() { return this->width; }
            std::size_t get_height() { return this->height; }

            std::string to_string();
    };

    template <typename T>
    class InterpolatedCircularArray2D {
        private:
            CircularArray2D<T> data;
            T (*interpolation2D)(CircularArray2D<T> &array, double x, double y);

        public:
            InterpolatedCircularArray2D(const T arr[], std::size_t width, std::size_t height, T (*interpolation_method)(CircularArray2D<T> &array, double x, double y)) : data(arr, width, height), interpolation2D(interpolation_method) {}
            InterpolatedCircularArray2D(std::vector<T> arr, std::size_t width, std::size_t height, T (*interpolation_method)(CircularArray2D<T> &array, double x, double y)) : data(arr, width, height), interpolation2D(interpolation_method) {}

            T get2D(double x, double y);

            std::size_t get_width() { return this->data.get_width(); }
            std::size_t get_height() { return this->data.get_height(); }
    };

    template <typename T>
    T method_truncate(CircularArray2D<T> &array, double x, double y);

    template <typename T>
    T method_linear(CircularArray2D<T> &array, double x, double y);

}


#endif
