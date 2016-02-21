#ifndef __BUST_ARRAYS_H__
#define __BUST_ARRAYS_H__

#include <vector>

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

            ~CircularArray() { }
            uint32_t size() { return this->length; }

            const T& operator[](std::size_t i) const { return this->data[i % this->legnth]; }
            T& operator[](std::size_t i) { return this->data[i % this->length]; }
    };

}


#endif
