
#include "png.h"

namespace png {

    PNG::PNG(uint32_t width, uint32_t height) : crc() {
        ihdr.width = width;
        ihdr.height = height;
        ihdr.bitdepth = 8;
        ihdr.colortype = 6;
        ihdr.compression = 0;
        ihdr.filter = 0;
        ihdr.interlace = 0;

        this->buffer = new uint32_t[width * height];
        for (uint32_t i = 0; i < width * height; i++) {
            buffer[i] = 0;
        }
    }

    PNG::~PNG() {
        delete buffer;
    }

    void PNG::appendZLibStream(std::ostream &stream, uint8_t *data, uint16_t size) {
        stream.write(reinterpret_cast<char *>(const_cast<uint16_t *>(&ZLIB_HEADER)), sizeof(uint16_t));
        this->appendRawDeflateData(stream, data, size);
        uint32_t sum = this->adler.get(data, size);
        stream.write(reinterpret_cast<char *>(&sum), sizeof(uint32_t));
    }

    void PNG::appendRawDeflateBlock(std::ostream &stream, uint8_t last, uint8_t *data, uint16_t size) {
        RawDeflateBlockHeader block;
        block.last = last;
        block.size = size;
        block.invsize = 0xffff ^ size;

        stream.write(reinterpret_cast<char *>(&block), sizeof(RawDeflateBlockHeader));
        stream.write(reinterpret_cast<char *>(data), size);
    }

    void PNG::appendRawDeflateData(std::ostream &stream, uint8_t *data, size_t size) {
        uint16_t chunks = size / DEFLATE_MAX_BLOCKSIZE;
        if (chunks < 1) {
            this->appendRawDeflateBlock(stream, 1, data, size);
            return;
        } 

        for (uint16_t i = 0; i < chunks-1; i++) {
            this->appendRawDeflateBlock(stream, 0, data + (DEFLATE_MAX_BLOCKSIZE * i), DEFLATE_MAX_BLOCKSIZE);
        }

        uint16_t rest = size % DEFLATE_MAX_BLOCKSIZE;
        if (rest > 0) {
            this->appendRawDeflateBlock(stream, 1, data + (DEFLATE_MAX_BLOCKSIZE * (chunks-1)), rest);
        }
    }

    void PNG::appendChunk(std::ostream &stream, uint32_t type, uint8_t *data, size_t size) {
        uint32_t typecrc = crc.get(0, reinterpret_cast<uint8_t *>(&type), sizeof(uint32_t));
        uint32_t finalcrc = crc.get(typecrc, data, size);

        stream.write(reinterpret_cast<char *>(&size), sizeof(uint32_t));
        stream.write(reinterpret_cast<char *>(&type), sizeof(uint32_t));
        stream.write(reinterpret_cast<char *>(data), size);
        stream.write(reinterpret_cast<char *>(&finalcrc), sizeof(uint32_t));
    }

    void PNG::append(std::ostream &stream) {

        // write header
        stream.write(reinterpret_cast<char *>(const_cast<uint32_t *>(&PNG_HEADER1)), sizeof(uint32_t));
        stream.write(reinterpret_cast<char *>(const_cast<uint32_t *>(&PNG_HEADER2)), sizeof(uint32_t));

        appendChunk(stream, CHUNK_TYPE_IHDR, reinterpret_cast<uint8_t *>(&this->ihdr), sizeof(IHDRChunk));
        std::stringstream zlibstream;
        this->appendZLibStream(zlibstream, reinterpret_cast<uint8_t *>(&this->buffer), this->ihdr.width * this->ihdr.height * sizeof(uint32_t));
        std::string zlibstream_str = zlibstream.str();
        appendChunk(stream, CHUNK_TYPE_IDAT, reinterpret_cast<uint8_t *>(const_cast<char *>(zlibstream_str.c_str())), zlibstream_str.length());
        appendChunk(stream, CHUNK_TYPE_IEND, nullptr, 0);
    }

}
