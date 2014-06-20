#include "test.h"
#include "suite.h"
#include "testing/test_testing.h"

int main (int argc, char *argv[]) {

     jarvis_testing::Suite *testingSuite = new jarvis_testing::Suite("Who Tests the Testers?");
     testingSuite->add(new jarvis_testing::TestingStatusTest());

     jarvis_testing::StdoutReport *report = new jarvis_testing::StdoutReport();
     testingSuite->add(report);

     testingSuite->run();

     return 0;
}
