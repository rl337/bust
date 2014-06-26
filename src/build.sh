#!/bin/bash

CMD="$1"

if [ "X$1" == "Xrebuild" ]; then
    rm -rf build
    mkdir -p build
    (
        cd build
        cmake ..
        if [ $? -ne 0 ]; then
            echo "cmake failed"
            exit 1
        fi
    )
fi

(
    cd build
    make
)
