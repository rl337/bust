#include "test_zlib.h"
#include "zlib.h"

#include <iostream>

namespace util {

    struct ZLibTestCase {
        std::string name;
        std::string input;
        std::string expected;
        ZLib zlib;

        ZLibTestCase(std::string name, std::string input, std::string expected) : name(name), input(input), expected(expected), zlib(32) {}
        ZLibTestCase(ZLibTestCase &other) : ZLibTestCase(other.name, other.input, other.expected) {}

        void execute(UtilZLibTest *t) {
            size_t len = this->input.length();
            uint8_t *data = reinterpret_cast<uint8_t *>(const_cast<char *>(this->input.c_str()));

            this->zlib.writeLast(data, len);

            std::stringstream buffer;
            this->zlib.append(buffer);
            std::string actual = buffer.str();
            
            t->assertEqualHex(this->name, this->expected, actual);
        }
    };

    ZLibTestCase util_zlib_cases[] = {
        {
            "ZLib: zero byte zlib",
            "",
            std::string(
                "\x78\x01\x01\x00\x00\xff\xff\x00\x00\x00\x01",
                11
            )
        },
        {
            "ZLib: one byte zlib",
            " ",
            std::string(
                "\x78\x01\x01\x01\x00\xfe\xff\x20\x00\x21\x00\x21",
                12
            )
        },
        {
            "ZLib: text string",
            "The quick brown fox jumps over the lazy dog",
            std::string(
                "\x78\x01\x00\x20\x00\xdf\xff\x54\x68\x65"
                "\x20\x71\x75\x69\x63\x6b\x20\x62\x72\x6f"
                "\x77\x6e\x20\x66\x6f\x78\x20\x6a\x75\x6d"
                "\x70\x73\x20\x6f\x76\x65\x72\x20\x74\x01"
                "\x0b\x00\xf4\xff\x68\x65\x20\x6c\x61\x7a"
                "\x79\x20\x64\x6f\x67\x5b\xdc\x0f\xda",
                59
            )
        },
    };


    void UtilZLibTest::run() {
        for (ZLibTestCase t : util_zlib_cases) {
            t.execute(this);        
        }
    }

}

