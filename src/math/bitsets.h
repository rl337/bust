#ifndef __BUST_MATH_BITSETS_H__
#define __BUST_MATH_BITSETS_H__

#include <cstddef>
#include <cstdint>

namespace bust::math {
    
    class BitSet {
        private:
            std::uint32_t content;
            std::size_t count;

        public:
            BitSet(std::uint32_t set) : content(set) {}
            BitSet() : content(0) {}

            void           set(std::uint32_t set);
            std::uint32_t   get();
            void           clear();

            std::size_t getCount();
            bool   contains(std::uint32_t set);
            void   add(std::uint32_t set);
            void   remove(std::uint32_t set);
            void   intersect(std::uint32_t set);
    };

}


#endif
