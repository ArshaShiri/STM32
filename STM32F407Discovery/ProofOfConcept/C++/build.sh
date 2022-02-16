#!/bin/sh
buildDir="./build"

if [ ! -d "$buildDir" ]; then
	mkdir $buildDir 
fi

cmake -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON -S ./ -B $buildDir
cd $buildDir
make

# Change the elf files to bin.
for elfFile in *.elf; do 
    arm-none-eabi-objcopy -O binary "$elfFile" "${elfFile%.elf}.bin"
done
