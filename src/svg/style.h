#ifndef __BUST_SVG_STYLE_H__
#define __BUST_SVG_STYLE_H__

#include "color.h"

#include <cstddef>
#include <string>


namespace bust::svg {

    struct Style {
        private:
            std::string name;
            bust::util::Color fill;
            bust::util::Color stroke;
            uint8_t stroke_width;

        public:
            Style(std::string n, bust::util::Color f, bust::util::Color s, uint8_t sw) : name(n), fill(f), stroke(s), stroke_width(sw) {};
            Style(std::string n, bust::util::Color f) : name(n), fill(f), stroke(bust::util::colors::None), stroke_width(0) {};

            inline std::string getName() const { return this->name; }
            inline bust::util::Color getFill() const { return this->fill; }
            inline bust::util::Color getStroke() const { return this->stroke; }
            inline std::uint8_t getStrokeWidth() const { return this->stroke_width; }
    };

    namespace styles {
        static const Style Default("default", bust::util::colors::None, bust::util::colors::Black, 2);
    }

}

#endif

