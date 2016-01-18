#include "test_bitsets.h"
#include "bitsets.h"

namespace math {

    void MathBitSetsTest::run() {

        math::BitSet b;

        this->assertEqual("Bitset should start empty", (uint32_t) 0, (uint32_t) b.get());

        b.add(1);
        this->assertEqual("Bitset should have lowest bit set", (uint32_t) 1, (uint32_t) b.get());
        b.add(4);
        this->assertEqual("Bitset should a second bit set", (uint32_t) 5, (uint32_t) b.get());
        b.add(4);
        this->assertEqual("Bitset should have be the same, adding the same bit does nothing", (uint32_t) 5, (uint32_t) b.get());
        b.add(8);
        this->assertEqual("Bitset should start empty", (uint32_t) 13, (uint32_t) b.get());

        b.remove(4);
        this->assertEqual("Removing the middle bit means only extreme values", (uint32_t) 9, (uint32_t) b.get());

        b.remove(8);
        this->assertEqual("Removing the end value brings us to 1", (uint32_t) 1, (uint32_t) b.get());

        b.set(127);
        this->assertEqual("set content to 127", (uint32_t) 127, (uint32_t) b.get());

        b.clear();
        this->assertEqual("set reset value to 0", (uint32_t) 0, (uint32_t) b.get());


        math::BitSet c;
        c.set(1 + 16 + 32);
        b.set(4 + 16 + 64);

        b.intersect(c.get());

        this->assertEqual("intersection should just be 16", (uint32_t) 16, (uint32_t) b.get());
    }

}

