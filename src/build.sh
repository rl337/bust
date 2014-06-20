#!/bin/bash

rm -rf build
mkdir -p build

(
    cd build
    cmake ..
    if [ $? -ne 0 ]; then
        echo "cmake failed"
        exit 1
    fi
    make
)
