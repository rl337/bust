
#include "png.h"

namespace bust::png {

    PixelOutOfBounds png_pixel_out_of_bounds;

    PNG::PNG(uint32_t width, uint32_t height) : crc() {
        this->width = width;
        this->height = height;
        this->bitdepth = 8;
        this->colortype = 6;
        this->compression = 0;
        this->filter = 0;
        this->interlace = 0;

        this->buffer = new uint32_t[width * height];
        for (uint32_t i = 0; i < width * height; i++) {
            buffer[i] = 0;
        }
    }

    PNG::PNG(PNG &other) {
        this->width = other.width;
        this->height = other.height;
        this->bitdepth = other.bitdepth;
        this->colortype = other.colortype;
        this->compression = other.compression;
        this->filter = other.filter;
        this->interlace = other.interlace;

        this->buffer = new uint32_t[other.width * other.height];
        for (uint32_t i = 0; i < other.width * other.height; i++) {
            buffer[i] = other.buffer[i];
        }
    }

    PNG::PNG(uint32_t width, uint32_t height, std::vector<bust::util::Color> data) : PNG(width, height) {
        if (data.size() < width * height) {
            throw png_pixel_out_of_bounds;        
        }

        for (uint32_t x = 0; x < width; x++) {
            for (uint32_t y = 0; y < height; y++) {
                this->set(x, y, data[x + y * width]);
            }
        }
    }

    PNG::~PNG() {
        delete buffer;
    }

    void PNG::set(uint32_t x, uint32_t y, uint32_t rgba) {
        if (x > this->width) {
            throw png_pixel_out_of_bounds;        
        }
        if (y > this->height) {
            throw png_pixel_out_of_bounds;        
        }

        this->buffer[y * this->width + x] = htonl(rgba);
    }

    bust::util::Color PNG::get(uint32_t x, uint32_t y) {
        if (x > this->width) {
            throw png_pixel_out_of_bounds;        
        }
        if (y > this->height) {
            throw png_pixel_out_of_bounds;        
        }

        return bust::util::Color(this->buffer[y * this->width + x]);
    }

    void PNG::clear(bust::util::Color color) {
        for (uint32_t x = 0; x < width; x++) {
            for (uint32_t y = 0; y < height; y++) {
                this->set(x, y, color);
            }
        }
    }

    void PNG::appendChunk(std::ostream &stream, uint32_t type, uint8_t *data, size_t size) {
        uint32_t ntype = htonl(type);
        uint32_t typecrc = crc.get(0, reinterpret_cast<uint8_t *>(&ntype), sizeof(uint32_t));
        uint32_t finalcrc = crc.get(typecrc, data, size);
        uint32_t nfinalcrc = htonl(finalcrc);

        uint32_t nsize = htonl(size);
        stream.write(reinterpret_cast<char *>(&nsize), sizeof(uint32_t));
        stream.write(reinterpret_cast<char *>(&ntype), sizeof(uint32_t));
        if (size > 0) {
            stream.write(reinterpret_cast<char *>(data), size);
        }
        stream.write(reinterpret_cast<char *>(&nfinalcrc), sizeof(uint32_t));
    }

    void PNG::makeIHDRContent(std::ostream &stream) {
        uint32_t nwidth = htonl(this->width);
        uint32_t nheight = htonl(this->height);

        stream.write(reinterpret_cast<char *>(&nwidth), sizeof(uint32_t));
        stream.write(reinterpret_cast<char *>(&nheight), sizeof(uint32_t));

        stream.write(reinterpret_cast<char *>(&this->bitdepth), sizeof(uint8_t));
        stream.write(reinterpret_cast<char *>(&this->colortype), sizeof(uint8_t));
        stream.write(reinterpret_cast<char *>(&this->compression), sizeof(uint8_t));
        stream.write(reinterpret_cast<char *>(&this->filter), sizeof(uint8_t));
        stream.write(reinterpret_cast<char *>(&this->interlace), sizeof(uint8_t));
    }

    void PNG::append(std::ostream &stream) {

        // write header
        uint32_t nheader1 = htonl(PNG_HEADER1);
        stream.write(reinterpret_cast<char *>(const_cast<uint32_t *>(&nheader1)), sizeof(uint32_t));
        uint32_t nheader2 = htonl(PNG_HEADER2);
        stream.write(reinterpret_cast<char *>(const_cast<uint32_t *>(&nheader2)), sizeof(uint32_t));

        std::stringstream tmpstream;
        this->makeIHDRContent(tmpstream);
        std::string ihdrstr = tmpstream.str();
        char *ihdrcstr = const_cast<char *>(ihdrstr.c_str());

        appendChunk(stream, CHUNK_TYPE_IHDR, reinterpret_cast<uint8_t *>(ihdrcstr), ihdrstr.length());

        tmpstream.str("");
        tmpstream.clear();

        util::ZLib zlib;
        uint8_t n = '\0';
        for (size_t line = 0; line < height-1; line++) {
            tmpstream.write(reinterpret_cast<char *>(&n), sizeof(uint8_t));
            tmpstream.write(reinterpret_cast<char *>(&this->buffer[line * width]), this->width * sizeof(uint32_t));
        }
        tmpstream.write(reinterpret_cast<char *>(&n), sizeof(uint8_t));
        tmpstream.write(reinterpret_cast<char *>(&this->buffer[(height-1) * width]), this->width * sizeof(uint32_t));
        std::string pixeldata = tmpstream.str();
        zlib.writeLast(pixeldata);

        std::stringstream deflated;
        zlib.append(deflated);
        std::string zlibstr = deflated.str();

        appendChunk(stream, CHUNK_TYPE_IDAT, reinterpret_cast<uint8_t *>(const_cast<char *>(zlibstr.c_str())), zlibstr.length());
        appendChunk(stream, CHUNK_TYPE_IEND, nullptr, 0);
    }

    void CustomPNG::plot(int64_t x, int64_t y) {
        if (x < 0 || x >= this->getWidth()) {
            return;
        }

        if (y < 0 || y >= this->getHeight()) {
            return;
        }

        this->set((uint32_t) x, (uint32_t) y, this->current);
    }

    void CustomPNG::rectangle(int64_t x, int64_t y, uint32_t width, uint32_t height) {
        for (int64_t a = x; a < x+width; a++) {
            this->plot(a, y);
            this->plot(a, y + height-1);
        }

        for (int64_t a = y+1; a < y+height; a++) {
            this->plot(x, a);
            this->plot(x + width-1, a);
        }
    }

    // first two are "to octant 0" send two are "from octant 0"
    const int64_t bresenham_octants[8][4][2] = {
        { { 1, 0}, { 0, 1},   { 1, 0},{ 0, 1} },
        { { 0, 1}, { 1, 0},   { 0, 1},{ 1, 0} },
        { { 0, 1}, {-1, 0},   { 0,-1},{ 1, 0} },
        { {-1, 0}, { 0, 1},   {-1, 0},{ 0, 1} },
        { {-1, 0}, { 0,-1},   {-1, 0},{ 0,-1} },
        { { 0,-1}, {-1, 0},   { 0,-1},{-1, 0} },
        { { 0,-1}, { 1, 0},   { 0, 1},{-1, 0} },
        { { 1, 0}, { 0,-1},   { 1, 0},{ 0,-1} },
    };

    void bresenham(CustomPNG *png, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, int octant) {
        int64_t tx1 = (int64_t) x1*bresenham_octants[octant][0][0] + (int64_t) y1*bresenham_octants[octant][0][1]; 
        int64_t ty1 = (int64_t) x1*bresenham_octants[octant][1][0] + (int64_t) y1*bresenham_octants[octant][1][1]; 

        int64_t tx2 = (int64_t) x2*bresenham_octants[octant][0][0] + (int64_t) y2*bresenham_octants[octant][0][1]; 
        int64_t ty2 = (int64_t) x2*bresenham_octants[octant][1][0] + (int64_t) y2*bresenham_octants[octant][1][1]; 

        int64_t dx = tx2 - tx1;
        int64_t dy = ty2 - ty1;

        int64_t D = 2*dy - dx;
        int64_t y = ty1;

        if (D > 0) {
            D = D - (2*dx);
        }

        //std::cout << "octant: " << octant << " tx1: " << tx1 << " tx2: " << tx2 << std::endl;
        for (int64_t x = tx1; x <= tx2; x++) {
            uint32_t tx = (uint32_t) ((int64_t) x*bresenham_octants[octant][2][0] + (int64_t) y*bresenham_octants[octant][2][1]); 
            uint32_t ty = (uint32_t) ((int64_t) x*bresenham_octants[octant][3][0] + (int64_t) y*bresenham_octants[octant][3][1]); 
            //std::cout << "(" << tx << "," << ty << ") ";
            
            png->plot(tx,ty);
            D = D + (2*dy);
            if (D > 0) {
                y = y + 1;
                D = D - (2*dx);
            }
        }
        //std::cout << std::endl;
    }

    void CustomPNG::circle(int64_t x, int64_t y, uint32_t r) {
        int64_t dx = r;
        int64_t dy = 0;
        int64_t decision = 1 - dx;

        while (dy <= dx) {
            plot( x + dx, y + dy ); // Octant 1
            plot( x + dy, y + dx ); // Octant 2
            plot( x - dx, y + dy ); // Octant 4
            plot( x - dy, y + dx ); // Octant 3
            plot( x - dx, y - dy ); // Octant 5
            plot( x - dy, y - dx ); // Octant 6
            plot( x + dx, y - dy ); // Octant 7
            plot( x + dy, y - dx ); // Octant 8
            dy++;
            if (decision <= 0) { decision += 2 * dy + 1; }
            else { dx--; decision += 2 * (dy - dx) + 1; }
        }
    }

    void CustomPNG::line(int64_t x1, int64_t y1, int64_t x2, int64_t y2) {
        int64_t dx = (int64_t) x2 - (int64_t) x1;
        int64_t dy = (int64_t) y2 - (int64_t) y1;

        if (dx == 0 && dy == 0) {
            plot(x1, y1);
            return;
        }

        uint32_t miny, maxy;
        if (dy > 0) {
            miny = y1;
            maxy = y2;
        } else {
            miny = y2;
            maxy = y1;
        }

        // We have a vertical line. 
        if (dx == 0) {
            for(uint32_t j = miny; j <= maxy; j++) {
                plot(x1, j);
            }
            return;
        }

        uint32_t minx, maxx;
        if (dx > 0) {
            minx = x1;
            maxx = x2;
        } else {
            minx = x2;
            maxx = x1;
        }

        // We have a horizontal line. 
        if (dy == 0) {
            for(uint32_t i = minx; i <= maxx; i++) {
                plot(i, y1);
            }
            return;
        }

        // at this point we know we have a diagonal line.
        // we also have a normalized min/max x and y

        int64_t adx = dx < 0 ? -dx : dx;
        int64_t ady = dy < 0 ? -dy : dy;
        
        // figure out which octant we're in
        if (dx > 0) {
            if (dy > 0) {
                if (ady > adx) {
                    // octant 1
                    bresenham(this, x1, y1, x2, y2, 1);
                } else {
                    // octant 0
                    bresenham(this, x1, y1, x2, y2, 0);
                }
            } else {
                if (ady > adx) {
                    // octant 6
                    bresenham(this, x1, y1, x2, y2, 6);
                } else {
                    // octant 7
                    bresenham(this, x1, y1, x2, y2, 7);
                }
            }
        } else {
            if (dy > 0) {
                if (ady > adx) {
                    // octant 2
                    bresenham(this, x1, y1, x2, y2, 2);
                } else {
                    // octant 3
                    bresenham(this, x1, y1, x2, y2, 3);
                }
            } else {
                if (ady > adx) {
                    // octant 5
                    bresenham(this, x1, y1, x2, y2, 5);
                } else {
                    // octant 4
                    bresenham(this, x1, y1, x2, y2, 4);
                }
            }
        }
    }

}
