#include "test_png.h"
#include "png.h"

#include <iostream>
#include <iomanip>
#include <sstream>

namespace bust::png {

    struct PNGTestCase {
        std::string name;
        std::string expected;
        PNG png;

        PNGTestCase(std::string name, std::string expected, PNG png) : name(name), expected(expected), png(png) {}
        PNGTestCase(PNGTestCase &other) : PNGTestCase(other.name, other.expected, other.png) {}

        void execute(PNGPNGTest *t) {
            std::stringstream buffer;
            this->png.append(buffer);
            std::string actual = buffer.str();
            
            t->assertEqualHex(this->name, this->expected, actual);
        }
    };

    const bust::util::Color O = bust::util::colors::White;
    const bust::util::Color X = bust::util::colors::Black;

    const bust::util::Color R = bust::util::colors::Red;
    const bust::util::Color G = bust::util::colors::Lime;
    const bust::util::Color B = bust::util::colors::Blue;

    PNGTestCase png_png_cases[] = {
        {
            "PNG: 1x1 'None' PNG",
            std::string(
                "\x89\x50\x4e\x47\x0d\x0a\x1a\x0a"
                "\x00\x00\x00\x0d\x49\x48\x44\x52"
                "\x00\x00\x00\x01\x00\x00\x00\x01"
                "\x08\x06\x00\x00\x00\x1f\x15\xc4"
                "\x89\x00\x00\x00\x10\x49\x44\x41"
                "\x54\x78\x01\x01\x05\x00\xfa\xff"
                "\x00\x00\x00\x00\x00\x00\x05\x00"
                "\x01\x64\x78\x95\x38\x00\x00\x00"
                "\x00\x49\x45\x4e\x44\xae\x42\x60"
                "\x82",
                73
            ),
            { 1, 1, { bust::util::colors::None } }
        },
        {
            "PNG: 3x1 RGB PNG",
            std::string(
                "\x89\x50\x4e\x47\x0d\x0a\x1a\x0a\x00\x00\x00\x0d\x49\x48\x44\x52"
                "\x00\x00\x00\x03\x00\x00\x00\x01\x08\x06\x00\x00\x00\x1b\xe0\x14"
                "\xb4\x00\x00\x00\x18\x49\x44\x41\x54\x78\x01\x01\x0d\x00\xf2\xff"
                "\x00\xff\x00\x00\xff\x00\xff\x00\xff\x00\x00\xff\xff\x23\xe9\x05"
                "\xfb\x41\xa1\x4e\x17\x00\x00\x00\x00\x49\x45\x4e\x44\xae\x42\x60"
                "\x82",
                81
            ),
            { 3, 1, { R, G, B } }
        },
        {
            "PNG: 1x3 RGB PNG",
            std::string(
                "\x89\x50\x4e\x47\x0d\x0a\x1a\x0a\x00\x00\x00\x0d\x49\x48\x44\x52"
                "\x00\x00\x00\x01\x00\x00\x00\x03\x08\x06\x00\x00\x00\x52\xdd\x65"
                "\x82\x00\x00\x00\x1a\x49\x44\x41\x54\x78\x01\x01\x0f\x00\xf0\xff"
                "\x00\xff\x00\x00\xff\x00\x00\xff\x00\xff\x00\x00\x00\xff\xff\x29"
                "\xe5\x05\xfb\xb9\x82\x63\x3b\x00\x00\x00\x00\x49\x45\x4e\x44\xae"
                "\x42\x60\x82",
                83
            ),
            { 1, 3, { R, G, B } }
        },
    };

    void printPNG(std::string title, PNG &png) {
        uint32_t width = png.getWidth();
        uint32_t height = png.getHeight();

        std::cout << title << std::endl;
        std::stringstream buff;
        for (uint32_t y = 0; y < width; y++) {
            for (uint32_t x = 0; x < height; x++) {
                buff << std::setw(8) << std::setfill('0') << std::hex << png.get(x, y).getValue() << " ";
            }
            buff << std::endl;
        }

        std::cout << buff.str() << std::endl;
    }

    struct PNGCustomPNGTestCase {
        std::string name;
        PNG expected;
        void (*op)(CustomPNG &png);

        void run(bust::testing::Test *t) {
        
            uint32_t width = this->expected.getWidth();
            uint32_t height = this->expected.getHeight();

            CustomPNG png(width, height);
            this->op(png);
            
            //printPNG(this->name, this->expected);
            //printPNG(this->name, png);

            for (uint32_t x = 0; x < width; x++) {
                for (uint32_t y = 0; y < height; y++) {
                    std::stringstream testname;
                    testname << this->name << " X: " << x << " Y: " << y;
                    t->assertEqualHex(testname.str(), this->expected.get(x, y).getValue(), png.get(x, y).getValue());
                }
            }
        }
    };

    PNGCustomPNGTestCase png_custom_png_cases[] = {
        { "Simple Rectangle",
            { 5, 5, {
                O, O, O, O, O,
                O, X, X, X, O,
                O, X, O, X, O,
                O, X, O, X, O,
                O, X, X, X, O,
            }},
            [](CustomPNG &png) { png.PNG::clear(O); png.setCurrentColor(X); png.rectangle(1, 1, 3, 4); },
        },
        { "Clipped Rectangle",
            { 5, 5, {
                O, O, O, O, O,
                O, O, O, O, O,
                O, O, O, X, X,
                O, O, O, X, O,
                O, O, O, X, O,
            }},
            [](CustomPNG &png) { png.PNG::clear(O); png.setCurrentColor(X); png.rectangle(3, 2, 3, 4); },
        },
        { "Vertical Lines",
            { 5, 5, {
                O, O, O, O, O,
                X, O, O, X, O,
                X, O, O, X, O,
                X, X, O, X, X,
                O, X, O, O, X,
            }},
            [](CustomPNG &png) {
                png.PNG::clear(O);
                png.setCurrentColor(X);
                png.line(0, 1, 0, 3);
                png.line(1, 3, 1, 5);
                png.line(3, 3, 3, 1);
                png.line(4, 5, 4, 3);
            },
        },
        { "Horizontal Lines",
            { 5, 5, {
                O, X, X, X, O,
                O, O, O, X, X,
                O, O, O, O, O,
                O, X, X, X, O,
                O, O, O, X, X,
            }},
            [](CustomPNG &png) {
                png.PNG::clear(O);
                png.setCurrentColor(X);
                png.line(1, 0, 3, 0);
                png.line(3, 1, 5, 1);
                png.line(3, 3, 1, 3);
                png.line(5, 4, 3, 4);
            },
        },
        { "1:1 diagonal Lines",
            { 5, 5, {
                X, O, O, O, X,
                O, X, O, X, O,
                O, O, X, O, O,
                O, X, O, X, O,
                X, O, O, O, X,
            }},
            [](CustomPNG &png) {
                png.PNG::clear(O);
                png.setCurrentColor(X);
                png.line(0, 0, 4, 4);
                png.line(4, 0, 0, 4);
            },
        },
        { "Octant diagonal Lines",
            { 9, 9, {
                O, O, X, O, O, O, X, O, O,
                O, O, X, O, O, O, X, O, O,
                X, X, O, X, O, X, O, X, X,
                O, O, X, X, O, X, X, O, O,
                O, O, O, O, X, O, O, O, O,
                O, O, X, X, O, X, X, O, O,
                X, X, O, X, O, X, O, X, X,
                O, O, X, O, O, O, X, O, O,
                O, O, X, O, O, O, X, O, O,
            }},
            [](CustomPNG &png) {
                png.PNG::clear(O);
                png.setCurrentColor(X);
                png.line(4, 4, 8, 2); // octant 0
                png.line(4, 4, 6, 0); // octant 1
                png.line(4, 4, 2, 0); // octant 2
                png.line(4, 4, 0, 2); // octant 3
                png.line(4, 4, 0, 6); // octant 4
                png.line(4, 4, 2, 8); // octant 5
                png.line(4, 4, 6, 8); // octant 6
                png.line(4, 4, 8, 6); // octant 7
            },
        },
        { "circles",
            { 9, 9, {
                O, O, X, X, X, X, X, O, O,
                O, X, O, O, O, O, O, X, O,
                X, O, O, X, X, X, O, O, X,
                X, O, X, O, O, O, X, O, X,
                X, O, X, O, O, O, X, O, X,
                X, O, X, O, O, O, X, O, X,
                X, O, O, X, X, X, O, O, X,
                O, X, O, O, O, O, O, X, O,
                O, O, X, X, X, X, X, O, O,
            }},
            [](CustomPNG &png) {
                png.PNG::clear(O);
                png.setCurrentColor(X);
                png.circle(4, 4, 2);
                png.circle(4, 4, 4);
            },
        },
    };

    void PNGPNGTest::run() {
        for (PNGTestCase t : png_png_cases) {
            t.execute(this);        
        }

        for (PNGCustomPNGTestCase t : png_custom_png_cases) {
            t.run(this);        
        }
    }

}

