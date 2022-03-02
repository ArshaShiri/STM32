#!/bin/sh
buildDir="./build"

if [ ! -d "$buildDir" ]; then
	mkdir $buildDir 
fi

cmake -S ./ -B $buildDir -DCMAKE_TOOLCHAIN_FILE=./cmake/hostToolchainForUnitTesting.cmake
cd $buildDir
make
