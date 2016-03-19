
#include <iostream>
#include "base64.h"
#include "test_base64.h"

namespace bust::util {

    struct Base64TestCase {
        std::string name;
        std::string input;
        std::string expected;
        Base64 base64;

        Base64TestCase(std::string name, std::string input, std::string expected) : name(name), input(input), expected(expected), base64() {}
        Base64TestCase(Base64TestCase &other) : Base64TestCase(other.name, other.input, other.expected) {}

        void execute(UtilBase64Test *t) {
            std::string actual = base64.encode(this->input);
            
            t->assertEqual(this->name, this->expected, actual);
        }
    };

    Base64TestCase util_base64_cases[] = {
        {
            "Base64: zero byte base64",
            "",
            ""    
        },
        {
            "Base64: single byte base64",
            "M",
            "TQ=="    
        },
        {
            "Base64: two byte base64",
            "Ma",
            "TWE="    
        },
        {
            "Base64: any carnal pleas",
            "any carnal pleas",
            "YW55IGNhcm5hbCBwbGVhcw=="    
        },
        {
            "Base64: any carnal pleasu",
            "any carnal pleasu",
            "YW55IGNhcm5hbCBwbGVhc3U="
        },
        {
            "Base64: any carnal pleasur",
            "any carnal pleasur",
            "YW55IGNhcm5hbCBwbGVhc3Vy"
        },
        {
            "Base64: any carnal pleasure",
            "any carnal pleasure",
            "YW55IGNhcm5hbCBwbGVhc3VyZQ=="
        },
    };

    void UtilBase64Test::run() {
        for (Base64TestCase t : util_base64_cases) {
            t.execute(this);        
        }
    }

}

