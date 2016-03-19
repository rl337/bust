#ifndef __JV_UTIL_ZLIB_H__
#define __JV_UTIL_ZLIB_H__

#include <cstdint>
#include <iostream>
#include <sstream>
#include <exception>
#include <arpa/inet.h>

#include "checksums.h"

namespace bust::util {

    static const std::string BASE64_CHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

    struct Base64Struct {
        union {
            char     chars[4];
            uint32_t bits;
        } value;

        char c1() { return (value.bits & 0x00003F00) >> 8; }
        char c2() { return (value.bits & 0x000FC000) >> 14; }
        char c3() { return (value.bits & 0x03F00000) >> 20; }
        char c4() { return (value.bits & 0xFC000000) >> 26; }
    };

    class Base64 {
        private:
            const std::string data;
            const char fill;

        public:
            Base64(const std::string lookup = BASE64_CHARS, char fill='=') : data(lookup), fill(fill) {}
            std::string encode(std::string str);
    };

}

#endif
