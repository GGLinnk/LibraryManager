#!/bin/bash

buildDir="linuxbuild"

if [ ! -d "$buildDir" ]; then
    mkdir "$buildDir"
fi

cd "$buildDir"

if [ ! -e "CMakeCache.txt" ]; then
    cmake ..
fi

cmake --build .
