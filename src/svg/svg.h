#ifndef __JV_SVG_H__
#define __JV_SVG_H__

#include <cstddef>
#include <string>
#include <vector>
#include <iostream>

#include "style.h"

namespace svg {

    class SVG {
        private:
            std::string title;
            std::string description;
    };

    class Shape {
        private:
            Style style;

        protected:
            void appendStyle(std::ostream &stream, Style &style);

        public:
            Shape();
            ~Shape();

            inline Style getStyle() { return this->style; }

            virtual void append(std::ostream &stream) = 0;
    };

    class Rectangle : public Shape {
        private:
            int x;
            int y;
            int width;
            int height;

            Style style;

        public:
            inline int getX() { return this->x; }
            inline int getY() { return this->y; }
            inline int getWidth() { return this->width; }
            inline int getHeight() { return this->height; }
 
            void append(std::ostream &stream);
    };

}

#endif
