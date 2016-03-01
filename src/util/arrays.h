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

            T& get2D(std::size_t x, std::size_t y) { return this->get(y * this->width + x); }

            std::string to_string();

    };

}


#endif
