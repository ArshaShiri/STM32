#!/bin/sh

printManual() {
	echo ""
	echo -t "\t-t Build for target."
	echo -h "\t-h Build for host."
	echo -a "\t-a Build all."
	echo -r "\t-r Rebuild"
	echo -d "\t-r Rebuild"
	exit 1
}

if [ $# -eq 0 ]; then
	printManual
	exit
fi

while getopts :htrad flag; do
	case "${flag}" in
	t) buildForTarget=true ;;
	h) buildForHost=true ;;
	a) buildForTarget=true buildForHost=true ;;
	r) rebuild=true ;;
	d) debug=true ;;
	\?)
		printManual
		exit
		;;
	esac
done

scriptDir=$PWD
buildDir="$PWD/build"
buildHostDir="$buildDir/host"
buildTargetDir="$buildDir/target"

if [ "$rebuild" = true ]; then
	if [ "$buildForHost" = true ]; then
		echo "Removing build host directory."
		rm -rf $buildHostDir
	fi

	if [ "$buildForTarget" = true ]; then
		echo "Removing build target directory."
		rm -rf $buildTargetDir
	fi
fi

mkdir -p $buildDir

if [ "$buildForHost" = true ]; then
	echo "Building for host:"

	mkdir -p $buildHostDir
	cmake -S ./ -B $buildHostDir -DCMAKE_TOOLCHAIN_FILE=./cmake/hostToolchainForUnitTesting.cmake -DBUILD_TESTS=ON
	cd $buildHostDir
	make
fi

if [ "$buildForTarget" = true ]; then
	echo "Building for target:"

	mkdir $buildTargetDir

	if [ "$debug" = true ]; then
		cmake -S ./ -B $buildTargetDir -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=./cmake/targetToolchain.cmake -DBUILD_TARGET=ON
	else
		echo "Default release build"
		cmake -S ./ -B $buildTargetDir -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=./cmake/targetToolchain.cmake -DBUILD_TARGET=ON
	fi

	cd $buildTargetDir
	make -j8

	echo "Creating bin files"
	find $buildTargetDir -name "*.elf" -exec sh -c 'exec arm-none-eabi-objcopy -O binary "$1" "${1%.elf}.bin"' sh {} \;

	echo "Fix the name of memory map files"
	find $buildTargetDir -name "*.map" -exec sh -c 'dir="$(dirname "$1")"; basename="$(basename "$dir")"; echo $basename; mv "$1" "${1%/*.map}"/$basename.map' sh {} \;

	echo "Creating object dumpt files"
	find $buildTargetDir -name "*.elf" -exec sh -c 'arm-none-eabi-objdump -h "$1" >"${1%.elf}".headers' sh {} \;
	find $buildTargetDir -name "*.elf" -exec sh -c 'arm-none-eabi-objdump -D "$1" >"${1%.elf}".disassemble' sh {} \;
	find $buildTargetDir -name "*.elf" -exec sh -c 'arm-none-eabi-objdump -d "$1" >"${1%.elf}".disassembleExe' sh {} \;

	echo "Saving artifacsts"

fi
