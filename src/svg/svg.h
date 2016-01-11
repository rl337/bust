#ifndef __JV_SVG_H__
#define __JV_SVG_H__

#include <cstddef>
#include <string>
#include <vector>
#include <iostream>

#include "style.h"

namespace svg {


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

    class Point {
        public:
            int x;
            int y;

            Point(int x, int y) : x(x), y(y) {}
            Point(const Point &p) : x(p.x), y(p.y) {}
    };

    class SVG : public Shape {
        private:
            std::string title;
            std::string description;

            int width;
            int height;

            std::vector<Shape *> shapes;
        public:
            SVG(std::string title, std::string description, int width, int height, std::vector<Shape *> shapes, Style style) : Shape(style), title(title), description(description), width(width), height(height), shapes(shapes) { }
            SVG(std::string title, std::string description, int width, int height, std::vector<Shape *> shapes) : SVG(title, description, width, height, shapes, styles::Default) { }
            SVG(std::string title, std::string description, std::vector<Shape *> shapes) : SVG(title, description, 0, 0, shapes) { }
            SVG(std::vector<Shape *> shapes) : SVG("", "", 0, 0, shapes) {}
            SVG(std::string title, std::string description, int width, int height, Shape *shapes[], std::size_t n, Style style);
            SVG(std::string title, std::string description, int width, int height, Shape *shapes[], std::size_t n) : SVG(title, description, width, height, shapes, n, styles::Default) { }
            SVG(std::string title, std::string description, Shape *shapes[], std::size_t n) : SVG(title, description, 0, 0, shapes, n, styles::Default) {}
            SVG(Shape *shapes[], std::size_t n) : SVG("", "", shapes, n) {}

            inline void add(Shape *shape) { this->shapes.push_back(shape); }

            void append(std::ostream &stream);
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

    class Circle : public Shape {
        private:
            int x;
            int y;
            int r;

        public:
            Circle(int x, int y, int r, Style s) : Shape(s), x(x), y(y), r(r) { }
            Circle(int x, int y, int r) : Shape(styles::Default), x(x), y(y), r(r) { }

            inline int getX() { return this->x; }
            inline int getY() { return this->y; }
            inline int getRadius() { return this->r; }
 
            void append(std::ostream &stream);
    };

    class Line : public Shape {
        private:
            int x1;
            int y1;
            int x2;
            int y2;

        public:
            Line(int x1, int y1, int x2, int y2, Style s) : Shape(s), x1(x1), y1(y1), x2(x2), y2(y2) { }
            Line(int x1, int y1, int x2, int y2) : Shape(styles::Default), x1(x1), y1(y1), x2(x2), y2(y2) { }

            inline int getX1() { return this->x1; }
            inline int getY1() { return this->y1; }
            inline int getX2() { return this->x2; }
            inline int getY2() { return this->y2; }
 
            void append(std::ostream &stream);
    };

    class Polyline : public Shape {
        private:
            std::vector<Point> points;

        public:
            Polyline(std::vector<Point> &points, Style s) : Shape(s), points(points) { }
            Polyline(std::vector<Point> &points) : Shape(styles::Default), points(points) { }
            Polyline(const Point points[], std::size_t n);
            Polyline(const Point points[], std::size_t n, Style s);

            inline std::vector<Point> *getPoints() { return new std::vector<Point>(this->points); }
            inline void add(const Point &p) { this->points.push_back(p); }
 
            void append(std::ostream &stream);
    };
}

#endif
