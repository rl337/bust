#include "widgets.h"
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
    uint32_t img_width = 320;
    uint32_t img_height = 240;

    uint32_t svg_width = img_width*2 + 32;
    uint32_t svg_height = img_height*3 + 24;


    ICAPNG truncate(img_width, img_height, bust::util::method_truncate<bust::util::Color>);
    ICAPNG linear(img_width, img_height, bust::util::method_linear<bust::util::Color>);
    ICAPNG cosine(img_width, img_height, bust::util::method_cosine<bust::util::Color>);

    bust::svg::TitledImageWithCaption truncateWidget(
        (uint32_t) 0, (uint32_t) 0,
        svg_width, img_height,
        truncate,
        "Method: Truncation",
        "This method simply calls floor() before derefrencing the underlying array."
    );

    bust::svg::TitledImageWithCaption linearWidget(
        (uint32_t) 0, (uint32_t) img_height + 8,
        svg_width, img_height,
        linear,
        "Method: Linear Interpolation",
        "This method linearly interpolates a value between all neighbors."
    );

    bust::svg::TitledImageWithCaption cosineWidget(
        (uint32_t) 0, (uint32_t) 2*img_height + 16,
        svg_width, img_height,
        cosine,
        "Method: Cosine Interpolation",
        "This method uses a cos function to calculate the distance between neighbors then linearly interpolates based on the cosine distance."
    );

    bust::svg::SVG svg(
        "Interpolation Functions",
        "Examples of images generated with different interpolation functions",
        svg_width,
        svg_height,
        { &truncateWidget, &linearWidget, &cosineWidget}
    );
    
    std::ofstream out("arrays.svg", std::fstream::out);
    svg.append(out);
    out.close();

    return 0;
}
