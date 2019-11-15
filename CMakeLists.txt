cmake_minimum_required(VERSION 3.10)
project(LatticeTools)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++11")

set(NC 2 CACHE STRING "number of colors for SU(NC)")

if(NC EQUAL 2)
	add_library(MCSU2Gaugefield src/MCSU2Gaugefield.cc)
	set(INTERFACE_TARGET MCSU2Gaugefield)
	set(SUN_INCLUDE "${SU2_ROOT}")
elseif(NC EQUAL 3)
	add_library(CL2QCDGaugefield src/CL2QCDGaugefield.cc)
	target_compile_definitions(CL2QCDGaugefield PUBLIC
		USE_PRNG_RANLUX
		LOG_LEVEL=OFF
	)
	set(INTERFACE_TARGET CL2QCDGaugefield)
	set(SUN_INCLUDE
		"${Tools_ROOT}/include"
		"${CL2QCD_ROOT}"
		"${SU3_ROOT}"
	)
else()
	message(FATAL_ERROR "NC must be 2 or 3")
endif()

include_directories(
	"${SUN_INCLUDE}"
	include
)

add_library(LinkPath src/LinkPath.cc)

install(TARGETS LinkPath "${INTERFACE_TARGET}" DESTINATION "${CMAKE_SOURCE_DIR}/lib")
