#!/bin/bash

CMD="$1"
BUILDDIR="build"
STARTDIR=`pwd`
CMD=build
TYPE=release

if [ ! -d "$BUILDDIR" ]; then
    mkdir -p "$BUILDDIR"
    if [ $? -ne 0 ]; then
        echo "Could not create $BUILDDIR"
        exit -1
    fi
    CMD=rebuild
fi

while [ "X$1" != X ]; do
    case $1 in 
        debug) TYPE=DEBUG
            ;;
        release) TYPE=DEBUG
            ;;
        rebuild) CMD=rebuild
            ;;
        build) CMD=build
            ;;
    esac

    shift
done

echo "CMD: $CMD, TYPE: $TYPE"

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
        cmake "$STARTDIR" -DCMAKE_BUILD_TYPE=$TYPE
        if [ $? -ne 0 ]; then
            echo "cmake failed"
            exit 1
        fi
    )
fi

(
    cd "$BUILDDIR"
    make
)

