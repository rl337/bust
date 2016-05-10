#include "test_text.h"
#include <sstream>
#include <vector>
#include "text.h"

namespace bust::util {

    struct TestData {
        std::string name;
        std::string txt;
        std::vector<std::string> e;
        int w;

        void execute(UtilTextTest *t) {
            util::TextSplitter splitter(this->txt, w);

            std::stringstream str;
            str.str("");
            
            int index = 0;
            while(splitter.next()) {
                std::stringstream msg;

                splitter.append(str);
                std::string part = str.str();
                str.str("");
                if (index > this->e.size()) {
                    msg << this->name << ": value past expected length " << this->e.size() << ": " << part;
                    t->fail(msg.str());
                }

                msg << this->name << ": mismatch at position " << index;
                t->assertEqual(msg.str(), this->e[index], part);

                index++; 
            }
            size_t rows = splitter.rows();
            t->assertEqual(name + " should have had expected rows", this->e.size(), rows);
        }
    };

    TestData cases[] = {
        {
            "Simple Wrapped Text",
            "omg Omg OMG!",
            {
                 "omg",
                 "Omg",
                 "OMG",
                 "!"
            },
            3,
        },
        {
            "Non-wrapping text",
            "Method: Truncation",
            {
                "Method: Truncation"
            },
            100,
        },
        {
            "Wrapping on same text",
            "Method: Truncation",
            {
                "Method:",
                "Truncation",
            },
            16
        },
    };


    void UtilTextTest::run() {

        for (TestData t : cases) {
            t.execute(this);
        }
        
    }

}

