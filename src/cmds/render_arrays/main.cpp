#include "png.h"
#include "color.h"
#include "arrays.h"
#include <fstream>
#include <vector>


int main (int argc, char *argv[]) {
    uint32_t width = 1024;
    uint32_t height = 768;

    std::vector<bust::util::Color> colors = {
        bust::util::vga16::Black, bust::util::vga16::Gray, bust::util::vga16::White,
        bust::util::vga16::Olive, bust::util::vga16::Lime, bust::util::vga16::Yellow,
        bust::util::vga16::Navy, bust::util::vga16::Blue, bust::util::vga16::Aqua,
    };
    std::size_t colors_width = 3;
    std::size_t colors_height = 3;

    bust::png::PNG png(width, height);
    bust::util::InterpolatedCircularArray2D<bust::util::Color> truncated = { colors, colors_width, colors_height, bust::util::method_truncate<bust::util::Color>};
    bust::util::InterpolatedCircularArray2D<bust::util::Color> linear = { colors, colors_width, colors_height, bust::util::method_linear<bust::util::Color>};

    double xscale = ((double) colors_width) / ((double) width);
    double yscale = ((double) colors_height) / ((double) height) * 2;
    for (uint32_t x = 0; x < width; x++) {
        for (uint32_t y = 0; y < height/2; y++) {
            double dx = xscale * x;
            double dy = yscale * y;

            png.set(x, y, truncated.get2D(dx, dy).getValue());
            png.set(x, height/2 + y, linear.get2D(dx, dy).getValue());
        }
    }
    
    std::ofstream out("arrays.png", std::fstream::out);
    png.append(out);
    out.close();

    return 0;
}
