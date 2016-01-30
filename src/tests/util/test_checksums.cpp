#include "test_checksums.h"
#include "checksums.h"

#include <iostream>

namespace util {
    static CRC32 crc32;
    static Adler32 adler32;

    struct Checksum32TestCase {
        std::string name;
        std::string input;
        uint32_t expected;
        Checksum32 *algorithm;

        void execute(UtilChecksumsTest *t) {
            size_t len = this->input.length();
            uint8_t *data = reinterpret_cast<uint8_t *>(const_cast<char *>(this->input.c_str()));

            uint32_t actual = this->algorithm->get(data, len);
            
            t->assertEqual(this->name, this->expected, actual);
        }
    };

    Checksum32TestCase util_checksum_cases[] = {
        {
            "CRC32: Wikipedia CRC example",
            "The quick brown fox jumps over the lazy dog",
            0x414fa339,
            &crc32
        },
        {
            "CRC32: non-prime bytes test",
            "omg wtf!",
            0x8866D46B, 
            &crc32
        },
        {
            "CRC32: zero byte test",
            "",
            0x0, 
            &crc32
        },
        {
            "Adler32: Wikipedia Adler32 example",
            "Wikipedia",
            0x11E60398, 
            &adler32
        },
        {
            "Adler32: zero byte test",
            "",
            0x01, 
            &adler32
        },
    };

    void UtilChecksumsTest::run() {
        for (Checksum32TestCase t : util_checksum_cases) {
            t.execute(this);        
        }
    }

}

