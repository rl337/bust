
#include "zlib.h"

namespace util {

    void ZLib::append(std::ostream &stream) {
        uint16_t header = htons(ZLIB_HEADER);
        stream.write(reinterpret_cast<char *>(const_cast<uint16_t *>(&header)), sizeof(uint16_t));

        std::string data = this->buffer.str();
        const char *rendered = data.c_str();
        stream.write(rendered, data.length());

        uint32_t nsum = htonl(this->sum);
        stream.write(reinterpret_cast<char *>(&nsum), sizeof(uint32_t));
    }

    void ZLib::appendRawDeflateBlock(uint8_t last, uint8_t *data, uint16_t size) {
        uint16_t nsize = size;
        uint16_t ninvsize = 0xffff ^ size;

        this->buffer.write(reinterpret_cast<char *>(&last), sizeof(uint8_t));
        this->buffer.write(reinterpret_cast<char *>(&nsize), sizeof(uint16_t));
        this->buffer.write(reinterpret_cast<char *>(&ninvsize), sizeof(uint16_t));

        this->buffer.write(reinterpret_cast<char *>(data), size);
    }

    void ZLib::write(uint8_t *data, size_t size, bool last) {

        if (this->last > 0) {
            throw zlib_write_after_last_error;
        }

        if (last) {
            this->last = 1;
        }

        this->sum = this->adler32.get(
            this->sum,
            data,
            size
        );

        uint16_t chunks = size / this->blocksize;
        if (chunks < 1) {
            this->appendRawDeflateBlock(last, data, size);
            return;
        } 

        for (uint16_t i = 0; i < chunks; i++) {
            this->appendRawDeflateBlock(0, data + (this->blocksize * i), this->blocksize);
        }

        uint16_t rest = size % this->blocksize;
        if (rest > 0) {
            this->appendRawDeflateBlock(last, data + (this->blocksize * chunks), rest);
        }
    }
}
