#!/bin/bash
mkdir -p build
cd build && cmake ..
cd ..
cmake --build build && ./build/main
