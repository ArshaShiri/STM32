#!/bin/sh
buildDir="./build"

if [ ! -d "$buildDir" ]; then
	mkdir $buildDir 
fi

cmake -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON -CMAKE_EXPORT_COMPILE_COMMANDS=ON -S . -B $buildDir
cd $buildDir
make
