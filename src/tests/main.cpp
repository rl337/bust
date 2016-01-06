#include "test.h"
#include "suite.h"
#include "runner.h"

#include "testing/testing_suite.h"
#include "math/math_suite.h"
#include "svg/svg_suite.h"

int main (int argc, char *argv[]) {

     testing::TestingSuite testingSuite;
     math::MathSuite mathSuite;
     svg::SVGSuite svgSuite;

     testing::Runner runner;
     runner.add(&testingSuite);
     runner.add(&mathSuite);
     runner.add(&svgSuite);

     testing::StdoutReport *report = new testing::StdoutReport();
     runner.add(report);

     runner.run();

     return 0;
}
