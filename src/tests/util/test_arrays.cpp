#include "test_arrays.h"

namespace bust::util {

    template <typename T, typename ArrayType, typename IndexType>
    struct UtilArraysTestData {
        std::string name;

        ArrayType array;
        T (*get)(ArrayType &array, IndexType &index);
        std::vector<IndexType> indexes;
        std::vector<T> expected;

        void run(bust::testing::Test *t) {
            for (std::size_t i = 0; i < this->indexes.size(); i++) {
                IndexType index = this->indexes[i];
                T expected = this->expected[i];
                T actual = this->get(this->array, index);
                
                t->assertEqual(this->name, expected, actual);
            }
        }
    };

    template <typename T>
    struct Coord2D {
        T x;
        T y;
    };

    UtilArraysTestData<int, CircularArray2D<int>, Coord2D<int>> util_arrays2d_tests[] = {
        { "Simple 2d int test",
          {
               {
                   32, 1, 71, 3,
                   32, 1, 71, 3,
                   32, 1, 71, 3,
                   32, 1, 71, 3,
               }, 4, 4
          },
          [](CircularArray2D<int> &array, Coord2D<int> &index) { return array.get2D(index.x, index.y); },
          { {0,0}, {2,2}, {3,3} },
          {32, 71, 3}
        },
        { "Simple 2d overlap int test",
          {
               {
                   32, 4, 76, 6,
                   31, 1, 75, 5,
                   30, 2, 71, 4,
                   29, 3, 79, 3,
               }, 4, 4
          },
          [](CircularArray2D<int> &array, Coord2D<int> &index) { return array.get2D(index.x, index.y); },
          { {4+0,4+0}, {4+2,4+2}, {4+3,4+3} },
          {32, 71, 3}
        }
    };

    void run_2D_arrays(bust::testing::Test *t) {
        for (UtilArraysTestData<int, CircularArray2D<int>, Coord2D<int>> test : util_arrays2d_tests) {
            test.run(t);
        }
    }

    UtilArraysTestData<int, CircularArray<int>, int> util_arrays_tests[] = {
        { "Simple int test",
            { {32, 1, 71, 3} },
            [](CircularArray<int> &array, int &index) { return array.get(index); },
            {0, 2, 3},
            {32, 71, 3}
        },
        { "int test of one element",
            { std::vector<int>({32, }) },
            [](CircularArray<int> &array, int &index) { return array.get(index); },
            {0, 2, 3},
            {32, 32, 32}
        }
    };

    void run_1D_arrays(bust::testing::Test *t) {
        for (UtilArraysTestData<int, CircularArray<int>, int> test : util_arrays_tests) {
            test.run(t);
        }
    }

    UtilArraysTestData<int, InterpolatedCircularArray2D<int>, Coord2D<double>> util_interpolatedarrays2d_tests[] = {
        { "Simple 2d trunc interpolation test",
          {
               {
                   32, 1, 71, 3,
                   32, 1, 71, 3,
                   32, 1, 71, 3,
                   32, 1, 71, 3,
               }, 4, 4,
               bust::util::method_truncate
          },
          [](InterpolatedCircularArray2D<int> &array, Coord2D<double> &index) { return array.get2D(index.x, index.y); },
          { {0.0,0.0}, {2.0,2.0}, {3.0,3.0}, {0.1, 0.1}, {0.7, 0.7}, {1.1, 1.1} },
          {32, 71, 3, 32, 32, 1}
        },
        { "Simple 2d linear interpolation test",
          {
               {
                   0,  10, -10,
                   50, 30, -50,
                  -20,-10, -40,
               }, 3, 3,
               bust::util::method_linear
          },
          [](InterpolatedCircularArray2D<int> &array, Coord2D<double> &index) { return array.get2D(index.x, index.y); },
          { {0.0,0.0}, {1.0,1.0}, {1.0,0.0}, {0.0, 1.0}, {0.5, 0.0}, {0.0, 0.5}, {0.5, 0.5}, {2.0, 0.0}, {2.0, 1.0}, {2.0, 2.0}, {3.0, 0.0}, {3.0, 1.0}, {3.0, 2.0} },
          {0, 30, 10, 50, 5, 25, (int) (0.0/4.0 + 10.0/4.0 + 50.0/4.0 + 30.0/4.0), -10, -50, -40, 0, 50, -20 }
        },
    };

    void run_2D_interpolated_arrays(bust::testing::Test *t) {
        for (UtilArraysTestData<int, InterpolatedCircularArray2D<int>, Coord2D<double>> test : util_interpolatedarrays2d_tests) {
            test.run(t);
        }
    }

    void UtilArraysTest::run() {
        run_1D_arrays(this);
        run_2D_arrays(this);
        run_2D_interpolated_arrays(this);
    }


}

