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
            Shape(Style s) : style(s) {}

            inline Style &getStyle() { return this->style; }

            virtual void append(std::ostream &stream) = 0;
    };

    class Rectangle : public Shape {
        private:
            int x;
            int y;
            int width;
            int height;

        public:
            Rectangle(int x, int y, int w, int h, Style s) : Shape(s), x(x), y(y), width(w), height(h) { }
            Rectangle(int x, int y, int w, int h) : Shape(styles::Default), x(x), y(y), width(w), height(h) { }

            inline int getX() { return this->x; }
            inline int getY() { return this->y; }
            inline int getWidth() { return this->width; }
            inline int getHeight() { return this->height; }
 
            void append(std::ostream &stream);
    };

}

#endif
