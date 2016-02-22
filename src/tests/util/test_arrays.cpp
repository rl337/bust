#include "test_arrays.h"

namespace bust::util {

    template <typename T>
    struct UtilArraysTestData {
        std::string name;
        std::vector<T> input;
        std::vector<std::size_t> indexes;
        std::vector<T> expected;

        void run(bust::testing::Test *t) {
            for (std::size_t i = 0; i < this->indexes.size(); i++) {
                T expected = this->expected[i];

                CircularArray<T> array(&this->input[0], this->input.size());
                
                std::size_t index = this->indexes[i];
                T actual = array[index];
                if (expected != actual) {
                    t->fail("value at index should be expected.");
                }
            }
        }
    };

    UtilArraysTestData<int> util_arrays_tests[] = {
        { "Simple int test",
            {32, 1, 71, 3},
            {0, 2, 3},
            {32, 71, 3}
        },
        { "int test of one element",
            {32},
            {0, 2, 3},
            {32, 32, 32}
        },
    };

    void UtilArraysTest::run() {
        for (UtilArraysTestData<int> test : util_arrays_tests) {
            test.run(this);
        }
    }


}

