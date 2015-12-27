#include "vector.h"
#include <exception>

namespace math {
    
    void Vector::translate(Vector *b) {
        if (b == nullptr) {
            throw vector_null_error;        
        }

        if (b->count != this->count) {
            throw vector_size_mismatch_error;
        }
        
        for (int i = 0; i < this->count; i++) {
            this->content[i] += b->content[i];
        }
    }

    inline void Vector::scale(double s) {
        for (int i = 0; i < this->count; i++) {
            this->content[i] *= s;
        }
    }

    inline void Vector::clear(double s) {
        for (int i = 0; i < this->count; i++) {
            this->content[i] = s;
        }
    }

    void Vector::clear() {
        clear(0);
    }

}

