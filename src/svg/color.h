#ifndef __JV_SVG_H__
#define __JV_SVG_H__

#include <cstddef>
#include <string>

namespace svg {

    struct Color {
        private:
            std::string name;
            std::string value;

        public:
            Color(std::string n, std::string v) : name(n), value(v) {};
            Color(std::string v) : name(v), value(v) {};

            inline std::string getName() const { return this->name; }
            inline std::string getValue() const { return this->value; }
    };

    namespace colors {
        static const Color AliceBlue("aliceblue");
        static const Color Azure("azure");
        static const Color BlanchedAlmond("blanchedalmond");
        static const Color BurlyWood("burlywood");
        static const Color Coral("coral");
        static const Color Cyan("cyan");
        static const Color DarkGray("darkgray");
        static const Color DarkMagenta("darkmagenta");
        static const Color DarkRed("darkred");
        static const Color DarkSlateGray("darkslategray");
        static const Color DeepPink("deeppink");
        static const Color DodgerBlue("dodgerblue");
        static const Color Fuchsia("fuchsia");
        static const Color Goldenrod("goldenrod");
        static const Color Grey("grey");
        static const Color Indigo("indigo");
        static const Color LavenderBlush("lavenderblush");
        static const Color LightCoral("lightcoral");
        static const Color LightGreen("lightgreen");
        static const Color LightSeaGreen("lightseagreen");
        static const Color LightSteelBlue("lightsteelblue");
        static const Color Linen("linen");
        static const Color MediumBlue("mediumblue");
        static const Color MediumSlateBlue("mediumslateblue");
        static const Color MidnightBlue("midnightblue");
        static const Color Navajowhite("navajowhite");
        static const Color OliveDrab("olivedrab");
        static const Color PaleGoldenrod("palegoldenrod");
        static const Color PapayaWhip("papayawhip");
        static const Color Plum("plum");
        static const Color RosyBrown("rosybrown");
        static const Color SandyBrown("sandybrown");
        static const Color Silver("silver");
        static const Color SlateGrey("slategrey");
        static const Color Tan("tan");
        static const Color Turqoise("turqoise");
        static const Color WhiteSmoke("whitesmoke");
    
        static const Color AntiqueWhite("antiquewhite");
        static const Color Beige("beige");
        static const Color Blue("blue");
        static const Color CadetBlue("cadetblue");
        static const Color CornflowerBlue("cornflowerblue");
        static const Color DarkBlue("darkblue");
        static const Color DarkGreen("darkgreen");
        static const Color DarkOliveGreen("darkolivegreen");
        static const Color DarkSalmon("darksalmon");
        static const Color DarkSlateGrey("darkslategrey");
        static const Color DeepSkyBlue("deepskyblue");
        static const Color Firebrick("firebrick");
        static const Color Gainsboro("gainsboro");
        static const Color Gray("gray");
        static const Color Honeydew("honeydew");
        static const Color Ivory("ivory");
        static const Color LawnGreen("lawngreen");
        static const Color LightCyan("lightcyan");
        static const Color LightGrey("lightgrey");
        static const Color LightSkyBlue("lightskyblue");
        static const Color LightYellow("lightyellow");
        static const Color Magenta("magenta");
        static const Color MediumOrchid("mediumorchid");
        static const Color MediumSpringGreen("mediumspringgreen");
        static const Color MintCream("mintcream");
        static const Color Navy("navy");
        static const Color Orange("orange");
        static const Color PaleGreen("palegreen");
        static const Color PeachPuff("peachpuff");
        static const Color PowderBlue("powderblue");
        static const Color RoyalBlue("royalblue");
        static const Color SeaGreen("seagreen");
        static const Color SkyBlue("skyblue");
        static const Color Snow("snow");
        static const Color Teal("teal");
        static const Color Violet("violet");
        static const Color Yellow("yellow");
    
        static const Color Aqua("aqua");
        static const Color Bisque("bisque");
        static const Color BlueViolet("blueviolet");
        static const Color Chartreuse("chartreuse");
        static const Color CornSilk("cornsilk");
        static const Color DarkCyan("darkcyan");
        static const Color DarkGrey("darkgrey");
        static const Color DarkOrange("darkorange");
        static const Color DarkSeaGreen("darkseagreen");
        static const Color DarkTurquoise("darkturquoise");
        static const Color DimGray("dimgray");
        static const Color FloralWhite("floralwhite");
        static const Color GhostWhite("ghostwhite");
        static const Color Green("green");
        static const Color HotPink("hotpink");
        static const Color Khaki("khaki");
        static const Color LemonChiffon("lemonchiffon");
        static const Color LightGoldenrodYellow("lightgoldenrodyellow");
        static const Color LightPink("lightpink");
        static const Color LightSlateGray("lightslategray");
        static const Color Lime("lime");
        static const Color Maroon("maroon");
        static const Color MediumPurple("mediumpurple");
        static const Color MediumTurquoise("mediumturquoise");
        static const Color MistyRose("mistyrose");
        static const Color OldLace("oldlace");
        static const Color OrangeRed("orangered");
        static const Color PaleTurquoise("paleturquoise");
        static const Color Peru("peru");
        static const Color Purple("purple");
        static const Color SaddleBrown("saddlebrown");
        static const Color Seashell("seashell");
        static const Color SlateBlue("slateblue");
        static const Color SpringGreen("springgreen");
        static const Color Thistle("thistle");
        static const Color Wheat("wheat");
        static const Color YellowGreen("yellowgreen");
    
        static const Color Aquamarine("aquamarine");
        static const Color Black("black");
        static const Color Brown("brown");
        static const Color Chocolate("chocolate");
        static const Color Crimson("crimson");
        static const Color DarkGoldenrod("darkgoldenrod");
        static const Color DarkKhaki("darkkhaki");
        static const Color DarkOrchard("darkorchid");
        static const Color DarkSlateBlue("darkslateblue");
        static const Color DarkViolet("darkvioldet");
        static const Color DimGrey("dimgrey");
        static const Color ForestGreen("forestgreen");
        static const Color Gold("gold");
        static const Color GreenYellow("greenyellow");
        static const Color IndianRed("indianred");
        static const Color Lavender("lavender");
        static const Color LightBlue("lightblue");
        static const Color LightGray("lightgray");
        static const Color LightSalmon("lightsalmon");
        static const Color LightSlateGrey("lightslategrey");
        static const Color LimeGreen("limegreen");
        static const Color MediumAquamarine("mediumaquamarine");
        static const Color MediumSeaGreen("mediumseagreen");
        static const Color MediumVioletRed("mediumvioletred");
        static const Color Moccasin("moccasin");
        static const Color Olive("olive");
        static const Color PaleVioletRed("palevioletred");
        static const Color Pink("pink");
        static const Color Salmon("salmon");
        static const Color Sienna("sienna");
        static const Color SlateGray("slategray");
        static const Color SteelBlue("steelblue");
        static const Color Tomato("tomato");
        static const Color White("white");
    }

}

#endif

