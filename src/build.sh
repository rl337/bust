#!/bin/bash

CMD="$1"
BUILDDIR="build"
STARTDIR=`pwd`

if [ "X$CMD" == "X" ]; then
    if [ ! -d "$BUILDDIR" ]; then
        echo "$BUILDDIR doesn't exist. forcing rebuild"
        CMD=rebuild
    fi
fi

if [ "X$CMD" == "Xrebuild" ]; then
    rm -rf "$BUILDDIR"
    mkdir -p "$BUILDDIR"
    (
        cd "$BUILDDIR"
        cmake "$STARTDIR"
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

