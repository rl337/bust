#include "svg.h"
#include "widgets.h"
#include "images.h"
#include <fstream>

int main (int argc, char *argv[]) {
    uint32_t width = 1024;
    uint32_t height = 768;

    bust::png::TestImage testimg(120, 120);
    bust::svg::TitledImageWithCaption widget((uint32_t) 0, (uint32_t) 0, width, height, testimg, "This is a test image", "This image helps demonstrates the space taken up by images in layouts");
    bust::svg::SVG svg("Widget Demo", "Document showing pre-defined widgets", width, height, {
        &widget
    });

    std::ofstream out("widgets.svg", std::fstream::out);
    svg.append(out);
    out.close();

    return 0;
}
