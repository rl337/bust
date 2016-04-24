#ifndef __BUST_PNG_IMAGES_H__
#define __BUST_PNG_IMAGES_H__

#include "png.h"

namespace bust::png {

    class TestImage : public CustomPNG {

        public:
            TestImage(uint32_t width, uint32_t height) : CustomPNG(width, height) { draw(); }
            void draw();
    };

    class ColorBars : public CustomPNG {

        public:
            ColorBars(uint32_t width, uint32_t height) : CustomPNG(width, height) { draw(); }
            void draw();
    };

}

#endif
