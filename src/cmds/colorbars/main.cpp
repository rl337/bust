#include "png.h"
#include <fstream>

int main (int argc, char *argv[]) {
    png::PNG png(1920, 1080);
    
    std::ofstream out("colorbars.png", std::fstream::out);
    png.append(out);
    out.close();

    return 0;
}
