#include "png.h"
#include "color.h"
#include <fstream>

int main (int argc, char *argv[]) {
    uint32_t width = 1024;
    uint32_t height = 768;
    bust::png::CustomPNG png(width, height);

    for (uint32_t x = 0; x < width; x++) {
        for (uint32_t y = 0; y < height; y++) {
            bust::util::Color color;

            if (y < height * 25 / 40) {
                switch (x * 7 / width) {
                    case 0: color = bust::util::vga16::Silver; break;
                    case 1: color = bust::util::vga16::Yellow; break;
                    case 2: color = bust::util::vga16::Aqua; break;
                    case 3: color = bust::util::vga16::Lime; break;
                    case 4: color = bust::util::vga16::Fuchsia; break;
                    case 5: color = bust::util::vga16::Red; break;
                    case 6: color = bust::util::vga16::Blue; break;
                }
            } else if (y >= height * 25 / 40 && y < height * 29/40) {
                switch (x * 7 / width) {
                    case 0: color = bust::util::vga16::Blue; break;
                    case 1: color = bust::util::vga16::Black; break;
                    case 2: color = bust::util::vga16::Fuchsia; break;
                    case 3: color = bust::util::vga16::Black; break;
                    case 4: color = bust::util::vga16::Aqua; break;
                    case 5: color = bust::util::vga16::Black; break;
                    case 6: color = bust::util::vga16::Silver; break;
                }
            } else {
                switch (x * 18 / width) {
                    case 0: color = bust::util::vga16::Navy; break;
                    case 1: color = bust::util::vga16::Navy; break;
                    case 2: color = bust::util::vga16::Navy; break;
                    case 3: color = bust::util::vga16::White; break;
                    case 4: color = bust::util::vga16::White; break;
                    case 5: color = bust::util::vga16::White; break;
                    case 6: color = bust::util::vga16::Purple; break;
                    case 7: color = bust::util::vga16::Purple; break;
                    case 8: color = bust::util::vga16::Purple; break;
                    case 9: color = bust::util::vga16::Black; break;
                    case 10: color = bust::util::vga16::Black; break;
                    case 11: color = bust::util::vga16::Black; break;
                    case 12: color = bust::util::vga16::White; break;
                    case 13: color = bust::util::vga16::Silver; break;
                    case 14: color = bust::util::vga16::Gray; break;
                    case 15: color = bust::util::vga16::Black; break;
                    case 16: color = bust::util::vga16::Black; break;
                    case 17: color = bust::util::vga16::Black; break;
                }
            }

            png.set(x, y, color);
        }
    }
    
    std::ofstream out("colorbars.png", std::fstream::out);
    png.append(out);
    out.close();

    return 0;
}
