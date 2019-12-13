#!/bin/bash

depends_template="\
Tools_ROOT=
SU2_ROOT=
SU3_ROOT=
CL2QCD_ROOT="

if [ -s dependencies ]; then
	cmake_defines="$(cat dependencies | sed -r 's/^/-D/' | tr '\n' ' ')"
else
	echo -ne "$depends_template" > dependencies
	echo "dependencies not set .. creating template"
	exit
fi

(cd build

if [ "${1,,}" == su2 ]; then
	cmake $cmake_defines ..
elif [ "${1,,}" == su3 ]; then
	cmake -DNC=3 $cmake_defines ..
elif [ "$1" == clear ]; then
	rm -rf ../build/* ../lib/* ../bin/*
elif [ "$1" == clean ]; then
	make clean
	rm -rf ../lib/* ../bin/*
elif [ "$1" == "" ]; then
	make install
else
	echo "Invalid target '$1'"
fi

)