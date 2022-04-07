#!/bin/sh

printManual() {
	echo ""
	echo -t "\t-t Build for target."
	echo -h "\t-h Build for host."
	echo -r "\t-r Rebuild"
	exit 1
}

if [ $# -eq 0 ]; then
	printManual
	exit
fi

while getopts :htr flag; do
	case "${flag}" in
	t) buildForTarget=true ;;
	h) buildForHost=true ;;
	r) rebuild=true ;;
	\?)
		printManual
		exit
		;;
	esac
done

scriptDir=$PWD
buildDir="$PWD/build"

if [ "$rebuild" = true ]; then
	echo "Removing build directory."
	rm -rf $buildDir
fi

mkdir -p $buildDir

if [ "$buildForHost" = true ]; then
	echo "Building for host:"

	buildHostDir="$buildDir/host"
	mkdir -p $buildHostDir
	cmake -S ./ -B $buildHostDir -DCMAKE_TOOLCHAIN_FILE=./cmake/hostToolchainForUnitTesting.cmake
	cd $buildHostDir
	make
fi

if [ "$buildForTarget" = true ]; then
	echo "Building for target:"

	buildTargetDir="$buildDir/target"
	mkdir $buildTargetDir
	cmake -S ./ -B $buildTargetDir -DCMAKE_TOOLCHAIN_FILE=./cmake/targetToolchain.cmake
	cd $buildTargetDir
	make
fi
