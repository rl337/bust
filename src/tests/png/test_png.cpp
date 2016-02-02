#include "test_png.h"
#include "png.h"

#include <iostream>

namespace png {

    struct PNGTestCase {
        std::string name;
        std::string expected;
        PNG *png;

        PNGTestCase(std::string name, std::string expected, PNG *png) : name(name), expected(expected), png(png) {}
        PNGTestCase(PNGTestCase &other) : PNGTestCase(other.name, other.expected, other.png) {}

        void execute(PNGPNGTest *t) {
            std::stringstream buffer;
            this->png->append(buffer);
            std::string actual = buffer.str();
            
            t->assertEqualHex(this->name, this->expected, actual);
        }
    };

    class BlackPNG1x1 : public PNG {
        public:
            BlackPNG1x1() : PNG(1, 1) {
                set(0, 0, 0x00000000);
            }
    } black_png_1x1;

    class RGBPNG3x1 : public PNG {
        public:
            RGBPNG3x1() : PNG(3, 1) {
                set(0, 0, (uint32_t) 0xFF0000FF);
                set(1, 0, (uint32_t) 0x00FF00FF);
                set(2, 0, (uint32_t) 0x0000FFFF);
            }
    } rgb_png_3x1;

    class RGBPNG1x3 : public PNG {
        public:
            RGBPNG1x3() : PNG(1, 3) {
                set(0, 0, (uint32_t) 0xFF0000FF);
                set(0, 1, (uint32_t) 0x00FF00FF);
                set(0, 2, (uint32_t) 0x0000FFFF);
            }
    } rgb_png_1x3;

    PNGTestCase png_png_cases[] = {
        {
            "PNG: 1x1 black PNG",
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
            &black_png_1x1
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
            &rgb_png_3x1
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
            &rgb_png_1x3
        },
    };

    void PNGPNGTest::run() {
        for (PNGTestCase t : png_png_cases) {
            t.execute(this);        
        }
    }

}

