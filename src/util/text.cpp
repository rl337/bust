
#include "text.h"

namespace bust::util {

    int find_last_space_before_len(std::string &str, size_t length, size_t start) {
        if (start >= str.length()) {
            return -1;
        }

        int last = -1;
        int curr = start;

        int stop = start + length;
        if ( str.length() < stop ) {
            stop = str.length();
        }

        while (curr < stop) {
            if (str[curr] == ' ') {
                last = curr;
            }
            curr++;
        }

        if (curr == str.length()) {
            return curr;
        }

        if (last == -1) {
            return curr;
        }

        return last;
    }

    bool TextSplitter::next() {
        if (this->end >= this->text.length()) {
            return false;
        }

        while (this->text[this->end] == ' ') {
            this->end++;
        }
        int index = find_last_space_before_len(this->text, this->width, this->end);
        if (index == -1) {
            return false;
        }

        this->start = this->end;
        this->end = index;

        return true;
    }

    void TextSplitter::append(std::ostream &stream) {
        stream << this->text.substr(this->start, this->end - this->start);
    }

    int TextSplitter::rows() {
        int index = find_last_space_before_len(this->text, this->width, 0);
        int splits = 0;
        while (index != -1 && index < this->text.length()) {
            index = find_last_space_before_len(this->text, this->width, index + 1);
            splits++;
        }

        return splits + 1;
    }

}

