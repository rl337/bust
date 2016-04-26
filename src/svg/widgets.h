#ifndef __BUST_SVG_WIDGETS_H__
#define __BUST_SVG_WIDGETS_H__

#include <cstddef>
#include <string>
#include <vector>
#include <iostream>

#include "svg.h"

namespace bust::svg {

    class Theme {
        private:
            Style container;
            Style title;
            Style text;

            std::uint8_t spacing;

            std::uint8_t text_width;
            std::uint8_t text_height;

        public:
            Theme(Style container, Style title, Style text, std::uint8_t spacing, uint8_t tw, uint8_t th) : container(container), title(title), text(text), spacing(spacing), text_width(tw), text_height(th) {}
            Theme(const Theme &o) : container(o.container), title(o.title), text(o.text), spacing(o.spacing), text_width(o.text_width), text_height(o.text_height) {}
            Style getContainerStyle() { return container; }
            Style getTitleStyle() { return title; }
            Style getTextStyle() { return text; }

            uint8_t  getSpacing() { return spacing; }
            uint8_t  getFontHeight() { return text_height; }
            uint8_t  getFontWidth() { return text_width; }
    };

    namespace themes {
        static const Theme Default(
            { "DefaultTheme::container",
                bust::util::colors::White,
                bust::util::colors::Silver,
                1,
                ""
            },
            {"DefaultTheme::title",
                bust::util::colors::None,
                bust::util::colors::None,
                0,
                "font-family: monospace; font-style: normal; font-size: 12px; font-weight: bold;"
            },
            {"DefaultTheme::text",
                bust::util::colors::None,
                bust::util::colors::None,
                0,
                "font-family: monospace; font-style: normal; font-size: 12px;"
            },
            8,
            12,
            12
        );
    }

    class TitledImageWithCaption : public Shape {
        private:
            Rectangle bounds;
            Image image;
            WrappedText title;
            WrappedText description;

        public:
            TitledImageWithCaption(int x, int y, int width, int height, bust::png::PNG &image, std::string title, std::string description, Theme t);
            TitledImageWithCaption(int x, int y, int width, int height, bust::png::PNG &image, std::string title, std::string description) : TitledImageWithCaption(x, y, width, height, image, title, description, themes::Default) {}
            TitledImageWithCaption(int x, int y, int width, int height, bust::png::PNG &image, std::string title);

            inline Image& getImage() { return this->image; }
            inline Rectangle& getBounds() { return this->bounds; }
            inline WrappedText& getTitle() { return this->title; }
            inline WrappedText& getDescription() { return this->description; }
 
            void append(std::ostream &stream);
    };

}

#endif
