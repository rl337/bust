#include "test.h"
#include "suite.h"
#include "testing/test_testing.h"
#include "math/test_bitsets.h"
#include "math/test_vector.h"
// #include "svg/svg_suite.h"

int main (int argc, char *argv[]) {

     testing::Suite *testingSuite = new testing::Suite("Who Tests the Testers?");
     testingSuite->add(new testing::TestingStatusTest());
     testingSuite->add(new math::MathBitSetsTest());
     testingSuite->add(new math::MathVectorTest());
 //    testingSuite->add(new svg::SVGColorTest());

     testing::StdoutReport *report = new testing::StdoutReport();

     testingSuite->run(report);

     delete testingSuite;

     return 0;
}
