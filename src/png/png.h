#ifndef __BUST_PNG_PNG_H__
#define __BUST_PNG_PNG_H__

#include <cstdint>
#include <iostream>
#include <sstream>
#include <arpa/inet.h>

#include "checksums.h"
#include "zlib.h"

namespace bust::png {

    class PNG {
        private:
             uint32_t *buffer;
             uint32_t width;
             uint32_t height;
             uint8_t bitdepth;
             uint8_t colortype;
             uint8_t compression;
             uint8_t filter;
             uint8_t interlace;

             util::CRC32 crc;

             void appendChunk(std::ostream &stream, uint32_t type, uint8_t *data, size_t size);

             // first part of header with 0x89 followed by 'PNG'
             const uint32_t PNG_HEADER1 = 0x89504E47;

             // 2nd part of header with DOS newline, 0x1A and Unix newline
             const uint32_t PNG_HEADER2 =  0x0D0A1A0A;

             const uint32_t CHUNK_TYPE_IHDR = 0x49484452;
             const uint32_t CHUNK_TYPE_IDAT = 0x49444154;
             const uint32_t CHUNK_TYPE_IEND = 0x49454e44;

             void makeIHDRContent(std::ostream &stream);
        public:
            PNG(uint32_t width, uint32_t height);
            ~PNG();

            void append(std::ostream &stream);
            void set(uint32_t x, uint32_t y, uint32_t value);
            uint32_t getWidth() const { return this->width; }
            uint32_t getHeight() const { return this->height; }
    };

    class PixelOutOfBounds: public std::exception {
        virtual const char* what() const throw() {
            return "attempt to set a pixel beyond bounds of image";
        }
    };

    extern PixelOutOfBounds png_pixel_out_of_bounds;

}

#endif
