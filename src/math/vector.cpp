#include "vector.h"

namespace math {

    Vector::Vector(std::size_t size) {
        this->content = new double[size];
        this->count = size;
        this->clear();
    }

    Vector::Vector(double *data, std::size_t offset, std::size_t size) {
        this->content = new double[size];
        this->count = size;
        for(std::size_t i = 0; i < size; i++) {
            this->content[i] = data[offset + i];
        }
    }

    Vector::Vector(double *data, std::size_t size) : Vector::Vector(data, (std::size_t) 0, size) { } 

    Vector::~Vector() {
        delete this->content;
        this->content = nullptr;
    }
    
    void Vector::translate(Vector *b) {
        if (b == nullptr) {
            throw vector_null_error;        
        }

        if (b->count != this->count) {
            throw vector_size_mismatch_error;
        }
        
        for (std::size_t i = 0; i < this->count; i++) {
            this->content[i] += b->content[i];
        }
    }

    double Vector::get(std::size_t index) {
        if (index >= this->count) {
            throw vector_bounds_error;
        }

        return this->content[index];
    }

    void Vector::set(std::size_t index, double v) {
        if (index >= this->count) {
            throw vector_bounds_error;
        }

        this->content[index] = v;
    }

    void Vector::scale(double s) {
        for (std::size_t i = 0; i < this->count; i++) {
            this->content[i] *= s;
        }
    }

    void Vector::clear(double s) {
        for (std::size_t i = 0; i < this->count; i++) {
            this->content[i] = s;
        }
    }

}

