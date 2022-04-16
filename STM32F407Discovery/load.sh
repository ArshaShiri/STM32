#!/bin/sh

printManual() {
	echo ""
	echo -p "\t-t Load the the desired program. Arguments to the flag are:\n led\n"
	exit 1
}

if [ $# -eq 0 ]; then
	printManual
	exit
fi

while getopts :p: flag; do
	case "${flag}" in
	p) program=${OPTARG};;
	\?)
		printManual
		exit
		;;
	esac
done

find -name "$program.bin" -exec st-flash --reset write {} 0x08000000 \;
