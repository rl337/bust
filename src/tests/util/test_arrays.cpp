#include "test_arrays.h"

namespace bust::util {

    template <typename T>
    struct UtilArrays2DTestData {
        std::string name;
        std::vector<T> input;
        std::vector<std::size_t> x_indexes;
        std::vector<std::size_t> y_indexes;
        std::vector<T> expected;

        void run(bust::testing::Test *t) {
            for (std::size_t i = 0; i < this->x_indexes.size(); i++) {
                T expected = this->expected[i];

                CircularArray2D<T> array(&this->input[0], 4, 4);
                
                std::size_t x_index = this->x_indexes[i];
                std::size_t y_index = this->y_indexes[i];
                T actual = array.get2D(x_index, y_index);
    
                //t->assertEqual(this->name, expected, actual);
                t->assertEqual(array.to_string(), expected, actual);
            }
        }
    };

    UtilArrays2DTestData<int> util_arrays2d_tests[] = {
        { "Simple 2d int test",
            { 
                32, 1, 71, 3,
                32, 1, 71, 3,
                32, 1, 71, 3,
                32, 1, 71, 3,
            },
            {0, 2, 3},
            {0, 2, 3},
            {32, 71, 3}
        },
        { "Simple 2d overlap int test",
            { 
                32, 1, 71, 3,
                32, 1, 71, 3,
                32, 1, 71, 3,
                32, 1, 71, 3,
            },
            {4+0, 4+2, 4+3},
            {4+0, 4+2, 4+3},
            {32, 71, 3}
        },
    };

    void run_2D_arrays(bust::testing::Test *t) {
        for (UtilArrays2DTestData<int> test : util_arrays2d_tests) {
            test.run(t);
        }
    }

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

    void run_1D_arrays(bust::testing::Test *t) {
        for (UtilArraysTestData<int> test : util_arrays_tests) {
            test.run(t);
        }
    }

    void UtilArraysTest::run() {
        run_1D_arrays(this);
        run_2D_arrays(this);
    }


}

