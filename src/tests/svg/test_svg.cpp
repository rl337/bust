#include "test_svg.h"
#include <sstream>
#include "png.h"

namespace bust::svg {

    struct TestData {
        Shape *s;
        std::string e;

        void execute(SVGSVGTest *t) {
            std::stringstream out;

            this->s->append(out);
            std::string s = out.str();
            t->assertEqual("", this->e, s);
        }
    };

    const Point triangle[] = {
        { 1, 1 },
        { -1, 1 },
        { 1, -1 }
    };

    class RGBPNG1x3 : public bust::png::PNG {
        public:
            RGBPNG1x3() : PNG(1, 3) {
                set(0, 0, bust::util::colors::Red);
                set(0, 1, bust::util::colors::Lime);
                set(0, 2, bust::util::colors::Blue);
            }
    } rgb_png_1x3;

    Shape *shapes[] = {
        new Circle(1, 3, 5)
    };

    Shape *images[] = {
        new Image(1, 3, rgb_png_1x3)
    };

    TestData cases[] = {
        {
            new Rectangle(1, 3, 5, 7),
            "<rect x=\"1\" y=\"3\" width=\"5\" height=\"7\" stroke=\"black\" stroke-width=\"2\"/>"
        },
        {
            new Line(8, 9, -3, -5),
            "<line x1=\"8\" y1=\"9\" x2=\"-3\" y2=\"-5\" stroke=\"black\" stroke-width=\"2\"/>"
        },
        {
            new Circle(5, 6, 13),
            "<circle cx=\"5\" cy=\"6\" r=\"13\" stroke=\"black\" stroke-width=\"2\"/>"
        },
        {
            new Polyline(triangle, 3),
            "<polyline points=\"1,1 -1,1 1,-1\" stroke=\"black\" stroke-width=\"2\"/>"
        },
        {
            new Text(10, 30, "omg Omg OMG!"),
            "<text x=\"10\" y=\"30\" stroke=\"black\" stroke-width=\"2\">omg Omg OMG!</text>"
        },
        {
            new SVG(shapes, 1),
            "<?xml version=\"1.0\" standalone=\"no\"?>\n<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n<svg version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n<circle cx=\"1\" cy=\"3\" r=\"5\" stroke=\"black\" stroke-width=\"2\"/>\n</svg>"
        },
        {
            new SVG("SVG Test", "Testing my SVGs", 640, 480, shapes, 1),
            "<?xml version=\"1.0\" standalone=\"no\"?>\n<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n<svg width=\"640px\" height=\"480px\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n<title>SVG Test</title>\n<desc>Testing my SVGs</desc>\n<circle cx=\"1\" cy=\"3\" r=\"5\" stroke=\"black\" stroke-width=\"2\"/>\n</svg>"
        },
        {
            new SVG(images, 1),
            "<?xml version=\"1.0\" standalone=\"no\"?>\n<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n<svg version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n<image x=\"1\" y=\"3\" width=\"1\" height=\"3\" xlink:href=\"data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAEAAAADCAYAAABS3WWCAAAAGklEQVR4AQEPAPD/AP8AAP8AAP8A/wAAAP//KeUF+7mCYzsAAAAASUVORK5CYII=\" />\n</svg>"
        },
        {
            new WrappedText(10, 30, "omg Omg OMG!", 3, 16),
            "<text x=\"10\" y=\"30\" stroke=\"black\" stroke-width=\"2\">omg<tspan x=\"10\" dy=\"16\">Omg</tspan><tspan x=\"10\" dy=\"16\">OMG</tspan><tspan x=\"10\" dy=\"16\">!</tspan></text>"
        },
        {
            new WrappedText(10, 30, "Method: Truncation", 45, 12),
            "<text x=\"10\" y=\"30\" stroke=\"black\" stroke-width=\"2\">Method: Truncation</text>"
        },
        {
            new WrappedText(10, 30, "Method: Truncation", 16, 12),
            "<text x=\"10\" y=\"30\" stroke=\"black\" stroke-width=\"2\">Method:<tspan x=\"10\" dy=\"12\">Truncation</tspan></text>"
        },
    };


    void SVGSVGTest::run() {

        for (TestData t : cases) {
            t.execute(this);
        }
        
    }

}

