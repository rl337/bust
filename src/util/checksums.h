#ifndef __JV_MATH_CRC_H__
#define __JV_MATH_CRC_H__

#include <cstdint>

namespace util {

    class Checksum32 {
        public:
            virtual uint32_t get(uint32_t prev, uint8_t *bytes, size_t len) = 0;
            virtual uint32_t get(uint8_t *bytes, size_t len) { return this->get(0, bytes, len); }
    };

    class CRC32 : public Checksum32 {
        private:
            const uint32_t CRC_XOR = 0xedb88320;

            uint32_t *table;
        public:
            CRC32();
            ~CRC32();
            uint32_t get(uint32_t crc, uint8_t *bytes, size_t len);
            uint32_t get(uint8_t *bytes, size_t len);
    };

    class Adler32 : public Checksum32 {
        private:
            const uint32_t ADLER_MODULA = 65521;

        public:
            uint32_t get(uint32_t crc, uint8_t *bytes, size_t len);
            uint32_t get(uint8_t *bytes, size_t len);
    };
}

#endif
