#include "arrays.h"
#include "color.h"

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
    CircularArray<T>::CircularArray(std::vector<T> raw) : length(raw.size()), data(std::vector<T>(raw.size())) {
        for(std::size_t i = 0; i < raw.size(); i++) {
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


    template <typename T>
    T InterpolatedCircularArray2D<T>::get2D(double x, double y) {
        return this->interpolation2D(this->data, x, y);
    }

    std::size_t normalize_coord(double coord, double unit) {
        while (coord < 0.0) {
            coord += unit;
        }

        return (std::size_t) coord;
    }

    template <typename T>
    T method_truncate(CircularArray2D<T> &array, double x, double y) { 
        return array.get2D(normalize_coord(x, array.get_width()), normalize_coord(y, array.get_height()));
    }

    template <typename T>
    T method_linear(CircularArray2D<T> &array, double x, double y) { 
        double min_x = std::floor(x);
        double max_x = std::ceil(x);
        if (max_x == min_x) max_x += 1.0;
        double min_y = std::floor(y);
        double max_y = std::ceil(y);
        if (max_y == min_y) max_y += 1.0;

        double delta_min_x = x - min_x;
        double delta_max_x = max_x - x; 
        double delta_min_y = y - min_y;
        double delta_max_y = max_y - y;

        double width = (double) array.get_width();
        double height = (double) array.get_height();

        T ul = array.get2D(normalize_coord(min_x, width),  normalize_coord(min_y, height));
        T ur = array.get2D(normalize_coord(max_x, width),  normalize_coord(min_y, height));
        T ll = array.get2D(normalize_coord(min_x, width),  normalize_coord(max_y, height));
        T lr = array.get2D(normalize_coord(max_x, width),  normalize_coord(max_y, height));

        double ul_scale = (1.0 - delta_min_x) * (1.0 - delta_min_y);
        double ur_scale = (1.0 - delta_max_x) * (1.0 - delta_min_y);
        double ll_scale = (1.0 - delta_min_x) * (1.0 - delta_max_y);
        double lr_scale = (1.0 - delta_max_x) * (1.0 - delta_max_y);

        T result = ul * ul_scale + ur * ur_scale + ll * ll_scale + lr * lr_scale;
        return result;
    }

    template uint32_t method_truncate<uint32_t>(CircularArray2D<uint32_t> &array, double x, double y);
    template int method_truncate<int>(CircularArray2D<int> &array, double x, double y);

    template uint32_t method_linear<uint32_t>(CircularArray2D<uint32_t> &array, double x, double y);
    template int method_linear<int>(CircularArray2D<int> &array, double x, double y);

    template Color method_linear<Color>(CircularArray2D<Color> &array, double x, double y);
    template Color method_truncate<Color>(CircularArray2D<Color> &array, double x, double y);

    template class CircularArray<int>;
    template class CircularArray<uint32_t>;
    template class CircularArray<Color>;

    template class CircularArray2D<int>;
    template class CircularArray2D<uint32_t>;
    template class CircularArray2D<Color>;

    template class InterpolatedCircularArray2D<int>;
    template class InterpolatedCircularArray2D<uint32_t>;
    template class InterpolatedCircularArray2D<Color>;





}

