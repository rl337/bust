#include "color.h"

#ifndef __JV_SVG_STYLE_H__
#define __JV_SVG_STYLE_H__

#include <cstddef>
#include <string>


namespace svg {

    struct Style {
        private:
            std::string name;
            Color fill;
            Color stroke;
            uint8_t stroke_width;

        public:
            Style(std::string n, Color f, Color s, uint8_t sw) : name(n), fill(f), stroke(s), stroke_width(sw) {};
            Style(std::string n, Color f) : name(n), fill(f), stroke(colors::None), stroke_width(0) {};

            inline std::string getName() const { return this->name; }
            inline Color getFill() const { return this->fill; }
            inline Color getStroke() const { return this->stroke; }
            inline std::uint8_t getStrokeWidth() const { return this->stroke_width; }
    };

    namespace styles {
        static const Style Default("default", colors::None, colors::Black, 2);
    }

}

#endif

