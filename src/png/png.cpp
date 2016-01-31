
#include "png.h"

namespace png {

    PNG::PNG(uint32_t width, uint32_t height) : crc() {
        this->width = width;
        this->height = height;
        this->bitdepth = 8;
        this->colortype = 6;
        this->compression = 0;
        this->filter = 0;
        this->interlace = 0;

        this->buffer = new uint32_t[width * height];
        for (uint32_t i = 0; i < width * height; i++) {
            buffer[i] = 0;
        }
    }

    PNG::~PNG() {
        delete buffer;
    }

    void PNG::set(uint32_t x, uint32_t y, uint32_t rgba) {
        if (x > this->width) {
            throw png_pixel_out_of_bounds;        
        }
        if (y > this->height) {
            throw png_pixel_out_of_bounds;        
        }

        this->buffer[y * this->width + x] = htonl(rgba);
    }

    void PNG::appendChunk(std::ostream &stream, uint32_t type, uint8_t *data, size_t size) {
        uint32_t ntype = htonl(type);
        uint32_t typecrc = crc.get(0, reinterpret_cast<uint8_t *>(&ntype), sizeof(uint32_t));
        uint32_t finalcrc = crc.get(typecrc, data, size);
        uint32_t nfinalcrc = htonl(finalcrc);

        uint32_t nsize = htonl(size);
        stream.write(reinterpret_cast<char *>(&nsize), sizeof(uint32_t));
        stream.write(reinterpret_cast<char *>(&ntype), sizeof(uint32_t));
        stream.write(reinterpret_cast<char *>(data), size);
        stream.write(reinterpret_cast<char *>(&nfinalcrc), sizeof(uint32_t));
    }

    void PNG::makeIHDRContent(std::ostream &stream) {
        uint32_t nwidth = htonl(this->width);
        uint32_t nheight = htonl(this->height);

        stream.write(reinterpret_cast<char *>(&nwidth), sizeof(uint32_t));
        stream.write(reinterpret_cast<char *>(&nheight), sizeof(uint32_t));

        stream.write(reinterpret_cast<char *>(&this->bitdepth), sizeof(uint8_t));
        stream.write(reinterpret_cast<char *>(&this->colortype), sizeof(uint8_t));
        stream.write(reinterpret_cast<char *>(&this->compression), sizeof(uint8_t));
        stream.write(reinterpret_cast<char *>(&this->filter), sizeof(uint8_t));
        stream.write(reinterpret_cast<char *>(&this->interlace), sizeof(uint8_t));
    }

    void PNG::append(std::ostream &stream) {

        // write header
        uint32_t nheader1 = htonl(PNG_HEADER1);
        stream.write(reinterpret_cast<char *>(const_cast<uint32_t *>(&nheader1)), sizeof(uint32_t));
        uint32_t nheader2 = htonl(PNG_HEADER2);
        stream.write(reinterpret_cast<char *>(const_cast<uint32_t *>(&nheader2)), sizeof(uint32_t));

        std::stringstream tmpstream;
        this->makeIHDRContent(tmpstream);
        std::string ihdrstr = tmpstream.str();
        char *ihdrcstr = const_cast<char *>(ihdrstr.c_str());

        appendChunk(stream, CHUNK_TYPE_IHDR, reinterpret_cast<uint8_t *>(ihdrcstr), ihdrstr.length());

        tmpstream.str("");
        tmpstream.clear();

        util::ZLib zlib;
        uint8_t n = '\0';
        for (size_t line = 0; line < height-1; line++) {
            tmpstream.write(reinterpret_cast<char *>(&n), sizeof(uint8_t));
            tmpstream.write(reinterpret_cast<char *>(this->buffer + line * width * sizeof(uint32_t)), this->width * sizeof(uint32_t));
        }
        tmpstream.write(reinterpret_cast<char *>(&n), sizeof(uint8_t));
        tmpstream.write(reinterpret_cast<char *>(this->buffer + (height-1) * width * sizeof(uint32_t)), this->width * sizeof(uint32_t));
        std::string pixeldata = tmpstream.str();
        zlib.writeLast(pixeldata);

        std::stringstream deflated;
        zlib.append(deflated);
        std::string zlibstr = deflated.str();

        appendChunk(stream, CHUNK_TYPE_IDAT, reinterpret_cast<uint8_t *>(const_cast<char *>(zlibstr.c_str())), zlibstr.length());
        appendChunk(stream, CHUNK_TYPE_IEND, nullptr, 0);
    }

}
