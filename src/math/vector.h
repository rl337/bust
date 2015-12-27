#ifndef __JV_BITSETS_H__
#define __JV_BITSETS_H__

#include <cstddef>
#include <cstdint>
#include <exception>

namespace math {
    
    class Vector {
        private:
            double *content;
            std::size_t count;

        public:
            Vector(std::size_t length) : content(new double[length]), count(length) {}

            inline void           set(std::size_t index, double value);
            inline double         get(std::size_t index);
            inline void           clear();
            inline void           clear(double value);

            inline std::size_t    getSize() { return this->count; }
            void                  translate(Vector *b);
            inline void           scale(double s);
    };

    class VectorSizeMismatch: public std::exception {
        virtual const char* what() const throw() {
            return "Vector operation requires same sized vectors";
        }
    } vector_size_mismatch_error;

    class VectorNullException: public std::exception {
        virtual const char* what() const throw() {
            return "Vector operation requires non-null argument";
        }
    } vector_null_error;
}


#endif
