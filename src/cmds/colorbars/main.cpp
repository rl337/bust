#include "png.h"
#include "color.h"
#include <fstream>

int main (int argc, char *argv[]) {
    uint32_t width = 1024;
    uint32_t height = 768;
    bust::png::PNG png(width, height);

    for (uint32_t x = 0; x < width; x++) {
        for (uint32_t y = 0; y < height; y++) {
            uint32_t color;

            if (y < height * 25 / 40) {
                switch (x * 7 / width) {
                    case 0: color = bust::util::vga16::Silver.getValue(); break;
                    case 1: color = bust::util::vga16::Yellow.getValue(); break;
                    case 2: color = bust::util::vga16::Aqua.getValue(); break;
                    case 3: color = bust::util::vga16::Lime.getValue(); break;
                    case 4: color = bust::util::vga16::Fuchsia.getValue(); break;
                    case 5: color = bust::util::vga16::Red.getValue(); break;
                    case 6: color = bust::util::vga16::Blue.getValue(); break;
                }
            } else if (y >= height * 25 / 40 && y < height * 29/40) {
                switch (x * 7 / width) {
                    case 0: color = bust::util::vga16::Blue.getValue(); break;
                    case 1: color = bust::util::vga16::Black.getValue(); break;
                    case 2: color = bust::util::vga16::Fuchsia.getValue(); break;
                    case 3: color = bust::util::vga16::Black.getValue(); break;
                    case 4: color = bust::util::vga16::Aqua.getValue(); break;
                    case 5: color = bust::util::vga16::Black.getValue(); break;
                    case 6: color = bust::util::vga16::Silver.getValue(); break;
                }
            } else {
                switch (x * 18 / width) {
                    case 0: color = bust::util::vga16::Navy.getValue(); break;
                    case 1: color = bust::util::vga16::Navy.getValue(); break;
                    case 2: color = bust::util::vga16::Navy.getValue(); break;
                    case 3: color = bust::util::vga16::White.getValue(); break;
                    case 4: color = bust::util::vga16::White.getValue(); break;
                    case 5: color = bust::util::vga16::White.getValue(); break;
                    case 6: color = bust::util::vga16::Purple.getValue(); break;
                    case 7: color = bust::util::vga16::Purple.getValue(); break;
                    case 8: color = bust::util::vga16::Purple.getValue(); break;
                    case 9: color = bust::util::vga16::Black.getValue(); break;
                    case 10: color = bust::util::vga16::Black.getValue(); break;
                    case 11: color = bust::util::vga16::Black.getValue(); break;
                    case 12: color = bust::util::vga16::White.getValue(); break;
                    case 13: color = bust::util::vga16::Silver.getValue(); break;
                    case 14: color = bust::util::vga16::Gray.getValue(); break;
                    case 15: color = bust::util::vga16::Black.getValue(); break;
                    case 16: color = bust::util::vga16::Black.getValue(); break;
                    case 17: color = bust::util::vga16::Black.getValue(); break;
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
