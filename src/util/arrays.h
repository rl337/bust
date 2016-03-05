#ifndef __BUST_ARRAYS_H__
#define __BUST_ARRAYS_H__

#include <vector>
#include <sstream>

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
            CircularArray2D(const T arr[], std::size_t width = 16, std::size_t height = 16) : CircularArray<T>(arr, width * height), width(width), height(height) { }
            CircularArray2D(std::vector<T> arr, std::size_t width = 16, std::size_t height = 16) : CircularArray<T>(&arr[0], width * height), width(width), height(height) { }

            T& get2D(std::size_t x, std::size_t y) { return this->get(y * this->width + x); }
            std::size_t get_width() { return this->width; }
            std::size_t get_height() { return this->height; }

            std::string to_string();

    };

    template <typename T>
    class InterpolatedCircularArray2D {
        private:
            CircularArray2D<T> data;

        public:
            InterpolatedCircularArray2D(const T arr[], std::size_t width = 16, std::size_t height = 16) : data(arr, width, height) {}
            InterpolatedCircularArray2D(std::vector<T> arr, std::size_t width = 16, std::size_t height = 16) : data(&arr[0], width, height) {}

            T& get2D(double x, double y);
    };


}


#endif
