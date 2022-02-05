#!/bin/sh
buildDir="./build"

if [ ! -d "$buildDir" ]; then
	mkdir $buildDir 
fi

cmake -S . -B $buildDir
cd $buildDir
make
