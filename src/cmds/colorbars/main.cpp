#include "png.h"
#include <fstream>

int main (int argc, char *argv[]) {
    uint32_t width = 1024;
    uint32_t height = 768;
    png::PNG png(width, height);

    for (uint32_t x = 0; x < width; x++) {
        for (uint32_t y = 0; y < height; y++) {
            if ( x * 3 / width == 0) {
                png.set(x, y, 0xFF0000FF);
            }
            if ( x * 3 / width == 1) {
                png.set(x, y, 0x00FF00FF);
            }
            if ( x * 3 / width == 2) {
                png.set(x, y, 0x0000FFFF);
            }
        }
    }
    
    std::ofstream out("colorbars.png", std::fstream::out);
    png.append(out);
    out.close();

    return 0;
}
