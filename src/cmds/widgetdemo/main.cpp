#include "svg.h"
#include "widgets.h"
#include "images.h"
#include <fstream>

int main (int argc, char *argv[]) {
    uint32_t width = 1024;
    uint32_t height = 768;

    bust::png::TestImage testimg(480, 480);
    bust::svg::SVG svg("Widget Demo", "Document showing pre-defined widgets", width, height, {
        new bust::svg::TitledImageWithCaption((uint32_t) 30, (uint32_t) 30, testimg, "This is a test image", "This image helps demonstrates the space taken up by images in layouts"),
    });

    std::ofstream out("widgets.svg", std::fstream::out);
    svg.append(out);
    out.close();

    return 0;
}
