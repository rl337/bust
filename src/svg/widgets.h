#ifndef __BUST_SVG_WIDGETS_H__
#define __BUST_SVG_WIDGETS_H__

#include <cstddef>
#include <string>
#include <vector>
#include <iostream>

#include "svg.h"

namespace bust::svg {


    class TitledImageWithCaption : public Shape {
        private:
            Rectangle bounds;
            Image image;
            Text title;
            Text description;

        public:
            TitledImageWithCaption(int x, int y, bust::png::PNG &image, std::string title, std::string description, Style s);
            TitledImageWithCaption(int x, int y, bust::png::PNG &image, std::string title, std::string description) : TitledImageWithCaption(x, y, image, title, description, bust::svg::styles::Default) {}
            TitledImageWithCaption(int x, int y, bust::png::PNG &image, std::string title);

            inline Image& getImage() { return this->image; }
            inline Rectangle& getBounds() { return this->bounds; }
            inline Text& getTitle() { return this->title; }
            inline Text& getDescription() { return this->description; }
 
            void append(std::ostream &stream);
    };

}

#endif
