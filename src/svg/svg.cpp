
#include "svg.h"

namespace svg {

    SVG::SVG(std::string title, std::string description, int width, int height, Shape *shapes[], std::size_t n, Style style) : Shape(style), title(title), description(description), width(width), height(height) {
        for(std::size_t i = 0; i < n; i++) {
            this->add(shapes[i]);
        }
    }

    void SVG::append(std::ostream &stream) {
        stream << "<?xml version=\"1.0\" standalone=\"no\"?>" << std::endl;
        stream << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">" << std::endl;
        stream << "<svg ";
        if (this->width > 0) {
            stream << "width=\"" << this->width << "px\" ";
        }

        if (this->height > 0) {
            stream << "height=\"" << this->height <<  "px\" ";
        }

        stream << "version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">" << std::endl;

        if (this->title != "") {
            stream << "<title>" << this->title << "</title>" << std::endl;
        }

        if (this->description != "") {
            stream << "<desc>" << this->description << "</desc>" << std::endl;
        }


        for (Shape *shape : this->shapes) {
            shape->append(stream);
            stream << std::endl;
        }

        stream << "</svg>";
    }


    void Shape::appendStyle(std::ostream &stream, Style &style) {
         
        util::Color fill = style.getFill();
        if (fill != util::colors::None) {
            stream << "fill=\"" << fill.getName() << "\" ";
        }

        util::Color stroke = style.getStroke();
        std::uint8_t stroke_width = style.getStrokeWidth();
        if (stroke != util::colors::None && stroke_width > 0) {
            stream << "stroke=\"" << stroke.getName() << "\" " <<
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

    void Circle::append(std::ostream &stream) {
        stream << 
            "<circle cx=\"" << this->x <<
            "\" cy=\"" << this->y <<
            "\" r=\"" << this->r << 
            "\" ";
         
        this->appendStyle(stream, this->getStyle());

        stream <<  "/>";
    }

    void Line::append(std::ostream &stream) {
        stream << 
            "<line x1=\"" << this->x1 <<
            "\" y1=\"" << this->y1 <<
            "\" x2=\"" << this->x2 << 
            "\" y2=\"" << this->y2 <<
            "\" ";
         
        this->appendStyle(stream, this->getStyle());

        stream <<  "/>";
    }

    Polyline::Polyline(const Point points[], std::size_t n, Style s) : Shape(s) {
        for (size_t i = 0; i < n; i++) {
            this->add(points[i]);
        }
    }

    Polyline::Polyline(const Point points[], std::size_t n) : Polyline(points, n, styles::Default) { }


    void Polyline::append(std::ostream &stream) {
        stream << "<polyline points=\"";
        std::size_t i = 0;
        for (Point p : this->points) {
            if (i++ > 0) {
                stream << " ";
            }
            stream << p.x << "," << p.y;
        }

        stream << "\" ";
         
        this->appendStyle(stream, this->getStyle());

        stream <<  "/>";
    }

}

