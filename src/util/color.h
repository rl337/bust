#ifndef __JV_UTIL_COLOR_H__
#define __JV_UTIL_COLOR_H__

#include <cstddef>
#include <iostream>
#include <iomanip>
#include <string>

namespace bust::util {

    struct Color {
        private:
            std::string name;
            union {
                uint8_t component[4];
                uint32_t rgba;
            } value;

        public:
            Color(const std::string n, uint32_t v) : name(n) { value.rgba = v; };
            Color(const std::string n) : Color(n, 0) {};
            Color(const Color &c) : Color(c.name, c.value.rgba) {};
            Color() : Color("Empty", 0x00000000) {};

            inline bool operator==(const Color &rhs) {
                return this->name == rhs.name && this->value.rgba == rhs.value.rgba;
            }

            inline bool operator!=(const Color &rhs) {
                return this->name != rhs.name || this->value.rgba != rhs.value.rgba;
            }

            Color operator*(const double rhs) {
                Color result(*this);
                result.value.component[3] = (uint8_t) ( (double) this->value.component[3] * rhs);
                result.value.component[2] = (uint8_t) ( (double) this->value.component[2] * rhs);
                result.value.component[1] = (uint8_t) ( (double) this->value.component[1] * rhs);

                // Don't scale the alpha channel
                // result.value.component[0] = (uint8_t) ( (double) this->value.component[0] * rhs);

                return result;
            }

            Color operator+(const Color &rhs) {
                Color result(*this);
                result.value.component[3] = this->value.component[3] + rhs.value.component[3];
                result.value.component[2] = this->value.component[2] + rhs.value.component[2];
                result.value.component[1] = this->value.component[1] + rhs.value.component[1];

                // Take the largest Alpha of the two. Don't actually add.
                if (this->value.component[0] > rhs.value.component[0]) {
                    result.value.component[0] = this->value.component[0];
                } else { 
                    result.value.component[0] = rhs.value.component[0];
                }

                return result;
            }

            inline std::string getName() const { return this->name; }
            inline uint32_t getValue() const { return this->value.rgba; }
    };

    std::ostream& operator<<(std::ostream &o, const Color &a);

    namespace vga16 {
        static const Color Black("black", 0x000000FF);
        static const Color Gray("gray", 0x808080FF);

        static const Color Maroon("maroon", 0x800000FF);
        static const Color Red("red", 0xFF0000FF);

        static const Color Olive("olive", 0x008000FF);
        static const Color Lime("lime", 0x00FF00FF);

        static const Color Yellow("lime", 0xFFFF00FF);

        static const Color Navy("navy", 0x000080FF);
        static const Color Blue("blue", 0x0000FFFF);

        static const Color Purple("purple", 0x800080FF);
        static const Color Fuchsia("fuchsia", 0xFF00FFFF);

        static const Color Teal("teal", 0x008080FF);
        static const Color Aqua("aqua", 0x00FFFFFF);

        static const Color Silver("silver", 0xC0C0C0FF);
        static const Color White("white", 0xFFFFFFFF);
    }

    namespace colors {
        static const Color None("none", 0x00000000);
        static const Color AliceBlue("aliceblue", 0xF0F8FFFF);
        static const Color Azure("azure", 0xF0FFFFFF);
        static const Color BlanchedAlmond("blanchedalmond", 0xFFEBCDFF);
        static const Color BurlyWood("burlywood", 0xDEB887FF);
        static const Color Coral("coral", 0xFF7F50FF);
        static const Color Cyan("cyan", 0x00FFFFFF);
        static const Color DarkGray("darkgray", 0xA9A9A9FF);
        static const Color DarkMagenta("darkmagenta", 0x8B008BFF);
        static const Color DarkRed("darkred", 0x8B0000FF);
        static const Color DarkSlateGray("darkslategray", 0x2F4F4FFF);
        static const Color DeepPink("deeppink", 0xFF1493FF);
        static const Color DodgerBlue("dodgerblue", 0x1E90FFFF);
        static const Color Fuchsia("fuchsia", 0xFF00FFFF);
        static const Color Goldenrod("goldenrod", 0xDAA520FF);
        static const Color Grey("grey", 0x808080FF);
        static const Color Indigo("indigo", 0x4B0082FF);
        static const Color LavenderBlush("lavenderblush", 0xFFF0F5FF);
        static const Color LightCoral("lightcoral", 0xF08080FF);
        static const Color LightGreen("lightgreen", 0x90EE90FF);
        static const Color LightSeaGreen("lightseagreen", 0x20B2AA);
        static const Color LightSteelBlue("lightsteelblue", 0xB0C4DEFF);
        static const Color Linen("linen", 0xFAF0E6FF);
        static const Color MediumBlue("mediumblue", 0x0000CDFF);
        static const Color MediumSlateBlue("mediumslateblue", 0x7B68EEFF);
        static const Color MidnightBlue("midnightblue", 0x191970FF);
        static const Color Navajowhite("navajowhite", 0xFFDEADFF);
        static const Color OliveDrab("olivedrab", 0x6B8E23FF);
        static const Color PaleGoldenrod("palegoldenrod", 0xEEE8AAFF);
        static const Color PapayaWhip("papayawhip", 0xFFEFD5FF);
        static const Color Plum("plum", 0xDDA0DDFF);
        static const Color Red("red", 0xFF000000);
        static const Color RosyBrown("rosybrown", 0xBC8F8F);
        static const Color SandyBrown("sandybrown", 0xF4A460FF);
        static const Color Silver("silver", 0xC0C0C0FF);
        static const Color SlateGrey("slategrey", 0x708090FF);
        static const Color Tan("tan", 0xD2B4BCFF);
        static const Color Turqoise("turqoise", 0x40E0D0FF);
        static const Color WhiteSmoke("whitesmoke", 0xF5F5F5FF);
    
        static const Color AntiqueWhite("antiquewhite", 0xFAEBD7FF);
        static const Color Beige("beige", 0xF5F5DCFF);
        static const Color Blue("blue", 0x0000FFFF);
        static const Color CadetBlue("cadetblue", 0x5F9EA0FF);
        static const Color CornflowerBlue("cornflowerblue", 0x6495EDFF);
        static const Color DarkBlue("darkblue", 0x00008BFF);
        static const Color DarkGreen("darkgreen", 0x006400FF);
        static const Color DarkOliveGreen("darkolivegreen", 0x556B2FFF);
        static const Color DarkSalmon("darksalmon", 0xE9967AFF);
        static const Color DarkSlateGrey("darkslategrey", 0x2F4F4FFF);
        static const Color DeepSkyBlue("deepskyblue", 0xBFFFFF);
        static const Color Firebrick("firebrick", 0xB22222FF);
        static const Color Gainsboro("gainsboro", 0xDCDCDCFF);
        static const Color Gray("gray", 0x808080FF);
        static const Color Honeydew("honeydew", 0xF0FFF0FF);
        static const Color Ivory("ivory", 0xFFFFF0FF);
        static const Color LawnGreen("lawngreen", 0x7CFC00FF);
        static const Color LightCyan("lightcyan", 0xE0FFFFFF);
        static const Color LightGrey("lightgrey", 0xD3D3D3FF);
        static const Color LightSkyBlue("lightskyblue", 0x87CEFAFF);
        static const Color LightYellow("lightyellow", 0xFFFFE0FF);
        static const Color Magenta("magenta", 0xFF00FFFF);
        static const Color MediumOrchid("mediumorchid", 0xBA55D3FF);
        static const Color MediumSpringGreen("mediumspringgreen", 0x00FA9A);
        static const Color MintCream("mintcream", 0xF5FFFAFF);
        static const Color Navy("navy", 0x000080FF);
        static const Color Orange("orange", 0xFFA500FF);
        static const Color Orchid("orchid", 0xDA70D6FF);
        static const Color PaleGreen("palegreen", 0x98FB98FF);
        static const Color PeachPuff("peachpuff", 0xFFDAB9FF);
        static const Color PowderBlue("powderblue", 0xB0E0E6FF);
        static const Color RoyalBlue("royalblue", 0x4169E1FF);
        static const Color SeaGreen("seagreen", 0x2E8B57FF);
        static const Color SkyBlue("skyblue", 0x87CEEBFF);
        static const Color Snow("snow", 0xFFFAFAFF);
        static const Color Teal("teal", 0x008080FF);
        static const Color Violet("violet", 0xEE82EEFF);
        static const Color Yellow("yellow", 0xFFFF00FF);
    
        static const Color Aqua("aqua", 0x00FFFFFF);
        static const Color Bisque("bisque", 0xFFE4C4FF);
        static const Color BlueViolet("blueviolet", 0x8A2BE2FF);
        static const Color Chartreuse("chartreuse", 0x7FFF00FF);
        static const Color CornSilk("cornsilk", 0xFFF8DCFF);
        static const Color DarkCyan("darkcyan", 0x008B8BFF);
        static const Color DarkGrey("darkgrey", 0xA9A9A9FF);
        static const Color DarkOrange("darkorange", 0xFF8C00FF);
        static const Color DarkSeaGreen("darkseagreen", 0x8FBC8FFF);
        static const Color DarkTurquoise("darkturquoise", 0x00CED1FF);
        static const Color DimGray("dimgray", 0x696969FF);
        static const Color FloralWhite("floralwhite", 0xFFFAF0FF);
        static const Color GhostWhite("ghostwhite", 0xF8F8FFFF);
        static const Color Green("green", 0x008000FF);
        static const Color HotPink("hotpink", 0xFF69B4FF);
        static const Color Khaki("khaki", 0xF0E68CFF);
        static const Color LemonChiffon("lemonchiffon", 0xFFFACDFF);
        static const Color LightGoldenrodYellow("lightgoldenrodyellow", 0xFAFAD2FF);
        static const Color LightPink("lightpink", 0xFFB6C1FF);
        static const Color LightSlateGray("lightslategray", 0x778899FF);
        static const Color Lime("lime", 0x00FF00FF);
        static const Color Maroon("maroon", 0x800000FF);
        static const Color MediumPurple("mediumpurple", 0x9370DBFF);
        static const Color MediumTurquoise("mediumturquoise", 0x48D1CCFF);
        static const Color MistyRose("mistyrose", 0xFFE4E1FF);
        static const Color OldLace("oldlace", 0xFDF5E6FF);
        static const Color OrangeRed("orangered", 0xFF4500FF);
        static const Color PaleTurquoise("paleturquoise", 0xAFEEEEFF);
        static const Color Peru("peru", 0xCD853FFF);
        static const Color Purple("purple", 0x800080FF);
        static const Color SaddleBrown("saddlebrown", 0x8B4513FF);
        static const Color Seashell("seashell", 0xFFF5EEFF);
        static const Color SlateBlue("slateblue", 0x708090FF);
        static const Color SpringGreen("springgreen", 0x00FF7FFF);
        static const Color Thistle("thistle", 0xD8BFD6FF);
        static const Color Wheat("wheat", 0xF5DEB3FF);
        static const Color YellowGreen("yellowgreen", 0x9ACD32FF);
    
        static const Color Aquamarine("aquamarine", 0x7FFFD4FF);
        static const Color Black("black", 0x000000FF);
        static const Color Brown("brown", 0xA52A2AFF);
        static const Color Chocolate("chocolate", 0xD2691EFF);
        static const Color Crimson("crimson", 0xDC143CFF);
        static const Color DarkGoldenrod("darkgoldenrod", 0xB8860BFF);
        static const Color DarkKhaki("darkkhaki", 0xBDB76BFF);
        static const Color DarkOrchard("darkorchid", 0x9932CCFF);
        static const Color DarkSlateBlue("darkslateblue", 0x483D8BFF);
        static const Color DarkViolet("darkviolet", 0x9400D3FF);
        static const Color DimGrey("dimgrey", 0x696969FF);
        static const Color ForestGreen("forestgreen", 0x228B22FF);
        static const Color Gold("gold", 0xFFD700FF);
        static const Color GreenYellow("greenyellow", 0xADFF2FFF);
        static const Color IndianRed("indianred", 0xCD5C5CFF);
        static const Color Lavender("lavender", 0xE6E6FAFF);
        static const Color LightBlue("lightblue", 0xADD8E6FF);
        static const Color LightGray("lightgray", 0xD3D3D3FF);
        static const Color LightSalmon("lightsalmon", 0xFFA07AFF);
        static const Color LightSlateGrey("lightslategrey", 0x778899);
        static const Color LimeGreen("limegreen", 0x32CD32FF);
        static const Color MediumAquamarine("mediumaquamarine", 0x66CDAAFF);
        static const Color MediumSeaGreen("mediumseagreen", 0x3CB371FF);
        static const Color MediumVioletRed("mediumvioletred", 0xC71585FF);
        static const Color Moccasin("moccasin", 0xFFE4B5FF);
        static const Color Olive("olive", 0x808000FF);
        static const Color PaleVioletRed("palevioletred", 0xDB7093FF);
        static const Color Pink("pink", 0xFFC0CBFF);
        static const Color Salmon("salmon", 0xFA8072FF);
        static const Color Sienna("sienna", 0xA0522DFF);
        static const Color SlateGray("slategray", 0x708090FF);
        static const Color SteelBlue("steelblue", 0x4682B4FF);
        static const Color Tomato("tomato", 0xFF6347FF);
        static const Color White("white", 0xFFFFFFFF);
    }

}

#endif

