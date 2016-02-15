#include "test.h"
#include "suite.h"
#include "runner.h"

#include "testing/testing_suite.h"
#include "math/math_suite.h"
#include "svg/svg_suite.h"
#include "util/util_suite.h"
#include "png/png_suite.h"

int main (int argc, char *argv[]) {

     bust::testing::TestingSuite testingSuite;
     bust::math::MathSuite mathSuite;
     bust::svg::SVGSuite svgSuite;
     bust::util::UtilSuite utilSuite;
     bust::png::PNGSuite pngSuite;

     bust::testing::Runner runner;
     runner.add(&testingSuite);
     runner.add(&mathSuite);
     runner.add(&svgSuite);
     runner.add(&utilSuite);
     runner.add(&pngSuite);

     bust::testing::StdoutReport report;
     runner.add(&report);

     runner.run();

     return 0;
}
