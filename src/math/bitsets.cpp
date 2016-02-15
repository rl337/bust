#include "bitsets.h"

namespace bust::math {
    
    std::size_t BitSet::getCount() {
        return this->count;
    }

    bool   BitSet::contains(std::uint32_t set) {
        return (this->content & set) == 0;
    }

    void   BitSet::add(std::uint32_t set) {
        this->content = this->content | set;
    }

    void   BitSet::remove(std::uint32_t set) {
        this->content = this->content & ~set;
    }

    void   BitSet::intersect(std::uint32_t set) {
        this->content = this->content & set;
    }

    void   BitSet::set(std::uint32_t set) {
        this->content = set;
    }

    std::uint32_t BitSet::get() {
        return this->content;
    }


    void   BitSet::clear() {
        this->set(0);
    }

}

