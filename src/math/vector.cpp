#include "vector.h"

namespace bust::math {

    Vector::Vector(std::size_t dimensions) : content(new double[dimensions]), dimensions(dimensions) {
        this->clear();
    }

    Vector::Vector(double *data, std::size_t offset, std::size_t dimensions) : Vector::Vector(dimensions) {
        for(std::size_t i = 0; i < dimensions; i++) {
            this->content[i] = data[offset + i];
        }
    }

    Vector::Vector(double *data, std::size_t dimensions) : Vector::Vector(data, (std::size_t) 0, dimensions) { } 

    Vector::~Vector() {
        delete[] this->content;
        this->content = nullptr;
    }
    
    void Vector::translate(Vector &b) {
        if (b.dimensions != this->dimensions) {
            throw vector_size_mismatch_error;
        }
        
        for (std::size_t i = 0; i < this->dimensions; i++) {
            this->content[i] += b.content[i];
        }
    }

    double Vector::get(std::size_t index) {
        if (index >= this->dimensions) {
            throw vector_bounds_error;
        }
        return this->content[index];
    }

    void Vector::set(std::size_t index, double v) {
        if (index >= this->dimensions) {
            throw vector_bounds_error;
        }
        this->content[index] = v;
    }

    double Vector::getMagnitude() {
        double sumsq = 0;
        for (int i = 0; i < this->dimensions; i++) {
            sumsq += std::pow(this->get(i), 2);
        }
        return std::abs(sqrt(sumsq));
    }

    double Vector::getDistance(Vector &b) {
        Vector r(b);
        Vector s(*this);
        
        r.scale(-1.0);
        s.translate(r);
        return s.getMagnitude();
    }

    void Vector::scale(double s) {
        for (std::size_t i = 0; i < this->dimensions; i++) {
            this->content[i] *= s;
        }
    }

    void Vector::scaleTo(double s) {
        double m = this->getMagnitude();
        double ratio = 0.0;
        if (m != 0.0) {
            ratio = s / m;
        }
        this->scale(ratio);
    }

    void Vector::clear(double s) {
        for (std::size_t i = 0; i < this->dimensions; i++) {
            this->content[i] = s;
        }
    }

}

