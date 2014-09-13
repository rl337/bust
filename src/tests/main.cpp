#include "test.h"
#include "suite.h"
#include "testing/test_testing.h"
#include "math/test_bitsets.h"

int main (int argc, char *argv[]) {

     testing::Suite *testingSuite = new testing::Suite("Who Tests the Testers?");
     testingSuite->add(new testing::TestingStatusTest());
     testingSuite->add(new math::MathBitSetsTest());

     testing::StdoutReport *report = new testing::StdoutReport();
     testingSuite->add(report);

     testingSuite->run();

     return 0;
}
