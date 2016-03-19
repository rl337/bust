
#include "base64.h"

namespace bust::util {

    std::string Base64::encode(std::string str) {
        if (str.size() < 1) {
            return "";
        }

        std::stringstream buffer;
        Base64Struct x;

        size_t batches = str.size() / 3;
        size_t remainder = str.size() % 3;

        for (size_t batch = 0; batch < batches; batch++) {
            x.value.chars[3] = str[batch * 3 + 0];
            x.value.chars[2] = str[batch * 3 + 1];
            x.value.chars[1] = str[batch * 3 + 2];
            
            buffer.write(&this->data[x.c4()], sizeof(char));
            buffer.write(&this->data[x.c3()], sizeof(char));
            buffer.write(&this->data[x.c2()], sizeof(char));
            buffer.write(&this->data[x.c1()], sizeof(char));
        }

        if (remainder == 0) {
            return buffer.str();
        }

        x.value.chars[3] = remainder >= 1 ? str[batches * 3 + 0] : 0;
        x.value.chars[2] = remainder >= 2 ? str[batches * 3 + 1] : 0;
        x.value.chars[1] = 0;

        buffer.write(&this->data[x.c4()], sizeof(char));
        buffer.write(&this->data[x.c3()], sizeof(char));
        buffer.write(remainder > 1 ? &this->data[x.c2()] : &this->fill, sizeof(char));
        buffer.write(&this->fill, sizeof(char));

        return buffer.str();
    }

}
