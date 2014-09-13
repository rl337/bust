#include "test_bitsets.h"
#include "bitsets.h"

namespace math {

    void MathBitSetsTest::run() {

        math::BitSet b;

        this->assertEqual("Bitset should start empty", 0, b.get());

        b.add(1);
        this->assertEqual("Bitset should have lowest bit set", 1, b.get());
        b.add(4);
        this->assertEqual("Bitset should a second bit set", 5, b.get());
        b.add(4);
        this->assertEqual("Bitset should have be the same, adding the same bit does nothing", 5, b.get());
        b.add(8);
        this->assertEqual("Bitset should start empty", 13, b.get());

        b.remove(4);
        this->assertEqual("Removing the middle bit means only extreme values", 9, b.get());

        b.remove(8);
        this->assertEqual("Removing the end value brings us to 1", 1, b.get());

        b.set(127);
        this->assertEqual("set content to 127", 127, b.get());

        b.clear();
        this->assertEqual("set reset value to 0", 0, b.get());


        math::BitSet c;
        c.set(1 + 16 + 32);
        b.set(4 + 16 + 64);

        b.intersect(c.get());

        this->assertEqual("intersection should just be 16", 16, b.get());
    }

}

