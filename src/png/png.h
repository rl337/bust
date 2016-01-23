#ifndef __JV_PNG_H__
#define __JV_PNG_H__

#include <cstdint>
#include <iostream>
#include <sstream>

#include "checksums.h"

namespace png {

    struct IHDRChunk {
        uint32_t width;
        uint32_t height;
        uint8_t bitdepth;
        uint8_t colortype;
        uint8_t compression;
        uint8_t filter;
        uint8_t interlace;
    };

    struct RawDeflateBlockHeader {
        uint8_t last;
        uint16_t size;
        uint16_t invsize;
    };

    class PNG {
        private:
             uint32_t *buffer;
             IHDRChunk ihdr;

             util::CRC32 crc;
             util::Adler32 adler;

             void appendChunk(std::ostream &stream, uint32_t type, uint8_t *data, size_t size);
             void appendRawDeflate(std::ostream &stream, uint8_t last, uint8_t *data, size_t size);
             void appendRawDeflateData(std::ostream &stream, uint8_t *data, size_t size);
             void appendRawDeflateBlock(std::ostream &stream, uint8_t last, uint8_t *data, uint16_t size);
             void appendZLibStream(std::ostream &stream, uint8_t *data, uint16_t size);

             // first part of header with 0x89 followed by 'PNG'
             // const uint32_t PNG_HEADER1 = 0x89504E47;
             const uint32_t PNG_HEADER1 = 0x474E5089;

             // 2nd part of header with DOS newline, 0x1A and Unix newline
             const uint32_t PNG_HEADER2 =  0x0D0A1A0A;

             const uint16_t ZLIB_HEADER =  0x7801;
             const uint16_t DEFLATE_MAX_BLOCKSIZE = 0xFFFF;

             //const uint32_t CHUNK_TYPE_IHDR = 0x49484452;
             const uint32_t CHUNK_TYPE_IHDR = 0x52444849;
             //const uint32_t CHUNK_TYPE_IDAT = 0x49444154;
             const uint32_t CHUNK_TYPE_IDAT = 0x54414449;
             //const uint32_t CHUNK_TYPE_IEND = 0x49454e44;
             const uint32_t CHUNK_TYPE_IEND = 0x444e4549;

        public:
            PNG(uint32_t width, uint32_t height);
            ~PNG();

            void append(std::ostream &stream);
            uint32_t getWidth() const { return this->ihdr.width; }
            uint32_t getHeight() const { return this->ihdr.height; }
    };

}

#endif
