#!/bin/bash
# Author: i-bot
# GitHub: https://github.com/i-bot

case $1 in
    "setup")
        ./cmake.sh clean
        cmake -H. -Bbuild
        ./cmake.sh
        ;;
    "refresh")
        cmake -H. -Bbuild
        ./cmake.sh
        ;;
    "debug")
        ./cmake.sh clean
        cmake -H. -Bbuild -DCMAKE_BUILD_TYPE=Debug
        ./cmake.sh
        ;;
    "clean")
        rm -rf build test_executable s-torrent
        ;;
    *)
        make -C build $1
        ;;
esac

if [ $# -gt 1 ]
    then
        shift
        ./cmake.sh $*
fi
