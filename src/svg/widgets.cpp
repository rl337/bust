#include "widgets.h"

namespace bust::svg {

    TitledImageWithCaption::TitledImageWithCaption(int x, int y, int width, int height, bust::png::PNG &png, std::string title, std::string description, Theme t) :
        Shape(t.getContainerStyle()),
        bounds(x, y, width, height, t.getContainerStyle()),
        image(x + t.getSpacing(), y + t.getSpacing(), png, t.getContainerStyle()),

        title(x + png.getWidth() + 2*t.getSpacing(), y + t.getSpacing() + t.getFontHeight(), title, (width - png.getWidth())/t.getFontWidth() + 1, t.getFontHeight(), t.getTitleStyle()),
        description(x + png.getWidth() + 2*t.getSpacing(), y + 2*t.getSpacing() + (this->title.rows() + 1) * t.getFontHeight(), description, (width - png.getWidth())/t.getFontWidth() + 1, t.getFontHeight(), t.getTextStyle())
    { }

    void TitledImageWithCaption::append(std::ostream &stream) {
        this->bounds.append(stream);
        this->image.append(stream);
        this->title.append(stream);
        this->description.append(stream);
    }

}

