#include "widgets.h"
#include "noise.h"
#include <fstream>
#include <vector>

class SurfacePNG : public bust::png::PNG {
    
    public:
        SurfacePNG(uint32_t width, uint32_t height, bust::util::UniformNoiseSurface<bust::util::Color> surface) : bust::png::PNG(width, height) {
 
            for (double x = 0; x < width; x++) {
                for (double y = 0; y < height; y++) {
                    this->set(x, y, surface.get(x, y));
                }
            }
        }
};

int main (int argc, char *argv[]) {
    uint32_t img_width = 320;
    uint32_t img_height = 240;

    uint32_t svg_width = img_width*2 + 32;
    uint32_t svg_height = img_height*3 + 24;

    bust::util::UniformRandomSource<bust::util::Color> src(5);
    bust::util::LowResUniformNoiseSurface<bust::util::Color> surface10(src, 1.0);
    bust::util::LowResUniformNoiseSurface<bust::util::Color> surface15(src, 0.5);
    bust::util::LowResUniformNoiseSurface<bust::util::Color> surface20(src, 0.25);

    SurfacePNG scale10(img_width, img_height, surface10);
    SurfacePNG scale15(img_width, img_height, surface15);
    SurfacePNG scale20(img_width, img_height, surface20);

    bust::svg::TitledImageWithCaption scale10Widget(
        (uint32_t) 0, (uint32_t) 0,
        svg_width, img_height,
        scale10,
        "Noise Surface: 1.0 Scale",
        "This is a Noise Surface that uses a 1:1 scaling between the underlying noise array and coords"
    );

    bust::svg::TitledImageWithCaption scale15Widget(
        (uint32_t) 0, (uint32_t) 240,
        svg_width, img_height,
        scale15,
        "Noise Surface: 1.5 Scale",
        "This is a Noise Surface that uses a 1:2 scaling between the underlying noise array and coords"
    );

    bust::svg::TitledImageWithCaption scale20Widget(
        (uint32_t) 0, (uint32_t) 480,
        svg_width, img_height,
        scale20,
        "Noise Surface: 2.0 Scale",
        "This is a Noise Surface that uses a 1:4 scaling between the underlying noise array and coords"
    );


    bust::svg::SVG svg(
        "Noise Surfaces",
        "Examples of images generated with noise surfaces at different scales",
        svg_width,
        svg_height,
        { &scale10Widget, &scale15Widget, &scale20Widget }
    );
    
    std::ofstream out("surfaces.svg", std::fstream::out);
    svg.append(out);
    out.close();

    return 0;
}
