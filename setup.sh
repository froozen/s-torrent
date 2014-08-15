#!/bin/bash

rm -rf build
mkdir -p build
cmake -H. -Bbuild
./build.sh
