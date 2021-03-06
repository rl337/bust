#ifndef __JV_UTIL_ZLIB_H__
#define __JV_UTIL_ZLIB_H__

#include <cstdint>
#include <iostream>
#include <sstream>
#include <exception>
#include <arpa/inet.h>

#include "checksums.h"

namespace bust::util {

    static const uint16_t ZLIB_HEADER =  0x7801;
    static const uint16_t ZLIB_DEFLATE_MAX_BLOCKSIZE = 0xFFFF;

    class ZLib {
        private:
             uint16_t blocksize;
             uint16_t last;
             uint32_t sum;
             std::stringstream buffer;
             Adler32 adler32;

             void appendRawDeflateBlock(uint8_t last, uint8_t *data, uint16_t size);

        public:

            ZLib(uint16_t blocksize) : blocksize(blocksize), last(0), sum(1) {}
            ZLib() : ZLib(ZLIB_DEFLATE_MAX_BLOCKSIZE) {}

            void append(std::ostream &stream);
            inline std::string str() { return buffer.str(); }
            void write(uint8_t *data, size_t size, bool last);
            void write(std::string data, bool last);

            inline void write(uint8_t *data, size_t size) { write(data, size, false); }
            inline void writeLast(uint8_t *data, uint16_t size) { write(data, size, true); }

            inline void write(std::string data) { write(data, false); }
            inline void writeLast(std::string data) { write(data, true); }
    };

    class WriteAfterLastBlock: public std::exception {
        virtual const char* what() const throw() {
            return "Attempt to write zlib block after last block was written";
        }
    };
    extern WriteAfterLastBlock zlib_write_after_last_error;

}

#endif
