#!/bin/bash

depends_template="\
Tools_ROOT=
SU2_ROOT=
SU3_ROOT=
CL2QCD_ROOT="

if [ -s dependencies ]; then
	cmake_defines=()
	while read -r line; do
		echo "${line}" | grep -qE '^[[:space:]]*$' || cmake_defines+=("-D${line}")
	done < <(cat dependencies)
else
	echo -ne "$depends_template" > dependencies
	echo "dependencies not set .. creating template"
	exit
fi

mkdir -p build

function add_cl2qcd_libs {
lib_dir="$1"

for dep in "${cmake_defines[@]}"; do
	if [[ "$dep" =~ ^-DCL2QCD_ROOT ]]; then
		CL2QCD_ROOT="$(echo "$dep" | sed -r 's/^.+=//')"
		break
	fi
done

ar -M <<EOM
OPEN ${lib_dir}/libCL2QCDGaugefield.a
ADDLIB ${CL2QCD_ROOT}/build/physics/algorithms/libalgorithms.a
ADDLIB ${CL2QCD_ROOT}/build/physics/lattices/libgaugefield.a
ADDLIB ${CL2QCD_ROOT}/build/physics/libprng.a
ADDLIB ${CL2QCD_ROOT}/build/meta/libmeta.a
ADDLIB ${CL2QCD_ROOT}/build/hardware/libhardware.a
ADDLIB ${CL2QCD_ROOT}/build/executables/libexceptions.a
ADDLIB ${CL2QCD_ROOT}/build/hardware/lattices/libhardware_lattices.a
ADDLIB ${CL2QCD_ROOT}/build/ildg_io/libildg_io.a
ADDLIB ${CL2QCD_ROOT}/build/contractioncode_io/libcontractioncode_io.a
ADDLIB ${CL2QCD_ROOT}/build/host_functionality/liblogger.a
ADDLIB ${CL2QCD_ROOT}/build/einhard/libeinhard.a
ADDLIB ${CL2QCD_ROOT}/build/host_functionality/libhost_functionality.a
ADDLIB ${CL2QCD_ROOT}/build/geometry/libgeometry.a
ADDLIB ${CL2QCD_ROOT}/build/hardware/code/libcode.a
ADDLIB ${CL2QCD_ROOT}/build/hardware/transfer/libtransfer.a
ADDLIB ${CL2QCD_ROOT}/build/hardware/buffers/libbuffers.a
ADDLIB ${CL2QCD_ROOT}/build/ranlux/libranlux.a
ADDLIB ${CL2QCD_ROOT}/build/crypto/libcrypto.a
ADDLIB ${CL2QCD_ROOT}/build/ildg_io/lime/liblime.a
ADDLIB ${CL2QCD_ROOT}/build/ildg_io/sourcefileParameters/libsourcefileParameters.a
SAVE
END
EOM
}

function add_mcsu2_libs {
lib_dir="$1"

for dep in "${cmake_defines[@]}"; do
	if [[ "$dep" =~ ^-DSU2_ROOT ]]; then
		SU2_ROOT="$(echo "$dep" | sed -r 's/^.+=//')"
		break
	fi
done

ar -rcs "${lib_dir}/libsu2.a" "${SU2_ROOT}/io.o" "${SU2_ROOT}/heatbath.o" "${SU2_ROOT}/ranlxs.o" "${SU2_ROOT}/ranlxd.o" "${SU2_ROOT}/ranlux.o"

ar -M <<EOM
OPEN ${lib_dir}/libMCSU2Gaugefield.a
ADDLIB ${lib_dir}/libsu2.a
SAVE
END
EOM

rm "${lib_dir}/libsu2.a"
}

function add_sun_libs {
lib_dir="$1"
[[ -f "${lib_dir}/libMCSU2Gaugefield.a" ]] && add_mcsu2_libs "$lib_dir"
[[ -f "${lib_dir}/libCL2QCDGaugefield.a" ]] && add_cl2qcd_libs "$lib_dir"
}


(cd build

if [ "${1,,}" == su2 ]; then
	cmake "${cmake_defines[@]}" ..
elif [ "${1,,}" == su3 ]; then
	if [ "${2,,}" == cc ]; then
		cmake -DNC=3 -DUSECC=ON "${cmake_defines[@]}" ..
	else
		cmake -DNC=3 "${cmake_defines[@]}" ..
	fi
elif [ "$1" == clear ]; then
	rm -rf ../build/* ../lib/* ../bin/*
elif [ "$1" == clean ]; then
	make clean
	rm -rf ../lib/* ../bin/*
elif [ "$1" == "" ]; then
	make install
	add_sun_libs "../lib"
else
	echo "Invalid target '$1'"
fi

)
