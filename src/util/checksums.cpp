#include "checksums.h"

namespace util {

    CRC32::CRC32() {
        table = new uint32_t[256];

        for (uint32_t i = 0; i < 256; i++) {
            uint32_t remainder = i;
            for (uint32_t b = 0; b < 8; b++) {
                if (remainder & 1) {
                    remainder >>= 1;
                    remainder ^= CRC_XOR;
                } else
                    remainder >>= 1;
            }
            table[i] = remainder;
        }

    }

    CRC32::~CRC32() {
        delete table;
    }

    uint32_t CRC32::get(uint32_t crc, uint8_t *bytes, size_t len) {
	crc = crc ^ ~0U;

	for (size_t i = 0; i < len; i++ ) {
		crc = table[(crc ^ *bytes++) & 0xFF] ^ (crc >> 8);
        }

	return crc ^ ~0U;
    }

    uint32_t CRC32::get(uint8_t *bytes, size_t len) {
        return get(0, bytes, len); 
    }


    uint32_t Adler32::get(uint32_t crc, uint8_t *bytes, size_t len) {
        uint32_t b = 0;
    
        for (size_t i = 0; i < len; ++i) {
            crc = (crc + bytes[i]) % ADLER_MODULA;
            b = (b + crc) % ADLER_MODULA;
        }
    
        return (b << 16) | crc;
    }
   
    uint32_t Adler32::get(uint8_t *bytes, size_t len) {
        return get(1, bytes, len);
    }
   

}

