#include "widgets.h"
#include "noise.h"
#include <fstream>
#include <vector>

class SurfacePNG : public bust::png::PNG {
    
    public:
        SurfacePNG(uint32_t width, uint32_t height, bust::util::NoiseSurface<bust::util::Color> &surface) : bust::png::PNG(width, height) {
 
            for (double x = 0; x < width; x++) {
                for (double y = 0; y < height; y++) {
                    this->set(x, y, surface.get(x, y));
                }
            }
        }
};

struct SurfaceExample {
    std::string title;
    std::string description;
    bust::util::NoiseSurface<bust::util::Color> *surface;
};

bust::util::UniformRandomSource<bust::util::Color> src(5);
std::vector<SurfaceExample> examples = {
    { "Noise Surface: 1.0 Scale",
      "This is a Noise Surface that uses a 1:1 scaling between the underlying noise array and coords",
      new bust::util::LowResUniformNoiseSurface<bust::util::Color>(src,  1.0),
    },
    { "Noise Surface: 2.0 Scale",
      "This is a Noise Surface that uses a 2:1 scaling between the underlying noise array and coords",
      new bust::util::LowResUniformNoiseSurface<bust::util::Color>(src,  1.0/2.0),
    },
    { "Noise Surface: 4.0 Scale",
      "This is a Noise Surface that uses a 4:1 scaling between the underlying noise array and coords",
      new bust::util::LowResUniformNoiseSurface<bust::util::Color>(src,  1.0/4.0),
    },
    { "Noise Surface: X 2.0 Scale",
      "This is a Noise Surface that uses a 2:1 scaling between the underlying noise array and coords only in X axis",
      new bust::util::LowResUniformNoiseSurface<bust::util::Color>(src,  1.0/2.0, 1.0),
    },
    { "Noise Surface: X 4.0 Scale",
      "This is a Noise Surface that uses a 4:1 scaling between the underlying noise array and coords only in X axis",
      new bust::util::LowResUniformNoiseSurface<bust::util::Color>(src,  1.0/4.0, 1.0),
    },
    { "Noise Surface: Y 2.0 Scale",
      "This is a Noise Surface that uses a 2:1 scaling between the underlying noise array and coords only in Y axis",
      new bust::util::LowResUniformNoiseSurface<bust::util::Color>(src,  1.0, 1.0/2.0),
    },
    { "Noise Surface: Y 4.0 Scale",
      "This is a Noise Surface that uses a 4:1 scaling between the underlying noise array and coords only in Y axis",
      new bust::util::LowResUniformNoiseSurface<bust::util::Color>(src,  1.0, 1.0/4.0),
    },
};

int main (int argc, char *argv[]) {
    uint32_t img_width = 120;
    uint32_t img_height = 120;

    uint32_t svg_columns = 3;

    uint32_t widget_width = (img_width*2.5);
    uint32_t widget_height = img_height;

    uint32_t svg_width = ((widget_width + 16) * svg_columns) + 16;
    uint32_t svg_height = ((widget_height + 16) * (examples.size() + svg_columns - examples.size() % svg_columns) ) / svg_columns + 16;

    bust::svg::SVG svg(
        "Noise Surfaces",
        "Examples of images generated with noise surfaces at different scales",
        svg_width,
        svg_height
    );

    uint32_t item = 0;
    for (SurfaceExample example : examples) {
         uint32_t col = item % svg_columns;
         uint32_t row = (item + svg_columns - col - 1) / svg_columns;
         SurfacePNG *png = new SurfacePNG(img_width, img_height, *example.surface);
         bust::svg::TitledImageWithCaption *widget = new bust::svg::TitledImageWithCaption(
             col * widget_width + col * 16,
             row * widget_height + row * 16,
             widget_width, widget_height,
             *png,
             example.title,
             example.description
         );
    
        svg.add(widget);
        item += 1;
    }

    std::ofstream out("surfaces.svg", std::fstream::out);
    svg.append(out);
    out.close();

    return 0;
}
