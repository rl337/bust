#include "images.h"
#include <fstream>

int main (int argc, char *argv[]) {
    uint32_t width = 1024;
    uint32_t height = 768;

    bust::png::ColorBars png(width, height);

    std::ofstream out("colorbars.png", std::fstream::out);
    png.append(out);
    out.close();

    return 0;
}
