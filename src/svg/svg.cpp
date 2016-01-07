
#include "svg.h"

namespace svg {

    void Shape::appendStyle(std::ostream &stream, Style &style) {
         
        Color fill = style.getFill();
        if (fill != colors::None) {
            stream << "fill=\"" << fill.getValue() << "\" ";
        }

        Color stroke = style.getStroke();
        std::uint8_t stroke_width = style.getStrokeWidth();
        if (stroke != colors::None && stroke_width > 0) {
            stream << "stroke=\"" << stroke.getValue() << "\" " <<
                "stroke-width=\"" << (int) stroke_width << "\"";
        }
    }


    void Rectangle::append(std::ostream &stream) {
        stream << 
            "<rect x=\"" << this->x <<
            "\" y=\"" << this->y <<
            "\" width=\"" << this->width << 
            "\" height=\"" << this->height << "\" ";
         
        this->appendStyle(stream, this->getStyle());

        stream <<  "/>";
    }

}

