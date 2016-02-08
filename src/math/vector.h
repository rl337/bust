#ifndef __JV_BITSETS_H__
#define __JV_BITSETS_H__

#include <cstddef>
#include <cstdint>
#include <exception>
#include <cmath>

namespace math {
    
    class Vector {
        private:
            double *content;
            std::size_t dimensions;

        public:
            Vector(std::size_t dimensions);
            Vector(Vector &v) : Vector(v.content, v.dimensions) {};
            Vector(double *data, std::size_t dimensions);
            Vector(double *data, std::size_t offset, std::size_t dimensions);
            ~Vector();

            void                  set(std::size_t index, double value);
            double                get(std::size_t index);

            inline void           clear() { this->clear(0.0); }
            void                  clear(double value);

            inline std::size_t    getDimensions() { return this->dimensions; }
            double                getMagnitude();
            double                getDistance(Vector &b);

            void                  translate(Vector &b);
            void                  scale(double s);
            void                  scaleTo(double s);
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

    class VectorBoundsException: public std::exception {
        virtual const char* what() const throw() {
            return "Vector operation exceeded bounds";
        }
    } vector_bounds_error;
}


#endif
