#!/bin/sh
buildDir="./build"

if [ ! -d "$buildDir" ]; then
	mkdir $buildDir 
fi

cmake -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON -S ./ -B $buildDir
cd $buildDir
make
