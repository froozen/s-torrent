#!/bin/bash

rm -rf build
mkdir -p build
cmake -Hsrc -Bbuild
./build.sh
