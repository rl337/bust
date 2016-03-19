#include "test.h"

namespace bust::util {

    class UtilBase64Test : public bust::testing::Test {

        public:
            UtilBase64Test() : bust::testing::Test("UtilBase64Test") {}

            void run();
            void init(){};
            void cleanup(){};
    };

}
