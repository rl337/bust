#include "widgets.h"

namespace bust::svg {

    TitledImageWithCaption::TitledImageWithCaption(int x, int y, bust::png::PNG &png, std::string title, std::string description, Style s) :
        Shape(s), bounds(x, y, png.getWidth(), png.getHeight()), image(x, y, png), title(x, y, title), description(x, y, description) {
    }


    void TitledImageWithCaption::append(std::ostream &stream) {
        this->bounds.append(stream);
        this->image.append(stream);
        this->title.append(stream);
        this->description.append(stream);
    }

}

