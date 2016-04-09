#include "svg.h"
#include "png.h"
#include "color.h"
#include "arrays.h"
#include <fstream>
#include <vector>

class ICAPNG : public bust::png::PNG {
    private:
        const std::vector<bust::util::Color> colors = {
            bust::util::vga16::Black, bust::util::vga16::Gray, bust::util::vga16::White,
            bust::util::vga16::Olive, bust::util::vga16::Lime, bust::util::vga16::Yellow,
            bust::util::vga16::Navy, bust::util::vga16::Blue, bust::util::vga16::Aqua,
        };
        const std::size_t colors_width = 3;
        const std::size_t colors_height = 3;
    
    public:
        ICAPNG(uint32_t width, uint32_t height, bust::util::Color (*method)(bust::util::CircularArray2D<bust::util::Color> &array, double x, double y)) : bust::png::PNG(width, height) {
 
            bust::util::InterpolatedCircularArray2D<bust::util::Color> array = { colors, colors_width, colors_height, method};
            double xscale = ((double) colors_width) / ((double) width);
            double yscale = ((double) colors_height) / ((double) height);
            for (uint32_t x = 0; x < width; x++) {
                for (uint32_t y = 0; y < height; y++) {
                    double dx = xscale * x;
                    double dy = yscale * y;

                    this->set(x, y, array.get2D(dx, dy));
                }
            }
        }
};

int main (int argc, char *argv[]) {
    uint32_t width = 320;
    uint32_t height = 240;

    ICAPNG truncate(width, height, bust::util::method_truncate<bust::util::Color>);
    ICAPNG linear(width, height, bust::util::method_linear<bust::util::Color>);
    ICAPNG cosine(width, height, bust::util::method_cosine<bust::util::Color>);
    bust::svg::Image truncateImage(0, 0, truncate);
    bust::svg::Image linearImage(0, height + 20, linear);
    bust::svg::Image cosineImage(0, height * 2 + 40, cosine);

    bust::svg::SVG svg(
        "Interpolation Functions",
        "Examples of images generated with different interpolation functions",
        2550,
        3300,
        { &truncateImage, &linearImage, &cosineImage}
    );
    
    std::ofstream out("arrays.svg", std::fstream::out);
    svg.append(out);
    out.close();

    return 0;
}
