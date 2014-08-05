#!/bin/bash

rm -rf build
mkdir -p build
cmake -Hsrc -Bbuild
make -C build
