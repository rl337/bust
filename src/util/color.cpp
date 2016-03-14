#include "color.h"

namespace bust::util {
    std::ostream& operator<<(std::ostream &o, const Color &a) {
        return o << "#" << std::setw(8) << std::setfill('0') << std::hex << a.getValue();
    }

}
