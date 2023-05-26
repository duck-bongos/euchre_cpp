#!/bin/bash
if [ ! -d build/ ]; then
    mkdir build
fi

# remove contents of build
rm -rf build/*

# rebuild it
cd build
cmake ..
cmake --build .
cd ..
