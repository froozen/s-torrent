#!/bin/bash
# Author: i-bot
# GitHub: https://github.com/i-bot

case $1 in
    "setup")
        echo "creating makefile"
        rm -rf build
        mkdir -p build
        cmake -H. -Bbuild
        ./cmake.sh
        ;;
    "clean")
        echo "removing build/ and libboost.asio-wrapper.a"
        rm -rf build libboost.asio-wrapper.a
        ;;
    *)
        echo "building "$1
        make -C build $1
        ;;
esac

if [ $# -gt 1 ]
    then
        shift
        ./cmake.sh $*
fi
