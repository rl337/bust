
#include <string>
#include <iostream>
#include <sstream>

namespace bust::util {

    class TextSplitter {
        private:
            int start;
            int end;
            int width;
            std::string &text;

        public:
            TextSplitter(std::string &t, int w) : start(0), end(0), width(w), text(t) { };

            bool next();
            void append(std::ostream &out);
            int rows();
    };
}
