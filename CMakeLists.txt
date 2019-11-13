cmake_minimum_required(VERSION 3.10)
project(LatticeTools)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++11")

set(NC 2 CACHE STRING "number of colors for SU(NC)")
if(NOT NC MATCHES "^[23]$")
	message(FATAL_ERROR "NC must be 2 or 3")
endif()

if(NC EQUAL 2)
	set(SUN_ROOT "${SU2_ROOT}")
elseif(NC EQUAL 3)
	set(SUN_ROOT "${SU3_ROOT}")
endif()

include_directories(
	"${SUN_ROOT}"
	include
)

if(NC EQUAL 2)
	add_library(MCSU2Interface src/MCSU2Interface.cc)
	set(INTERFACE_TARGET MCSU2Interface)
elseif(NC EQUAL 3)
	add_library(CL2QCDInterface src/CL2QCDInterface.cc)
	set(INTERFACE_TARGET CL2QCDInterface)
endif()

add_library(LinkPath src/LinkPath.cc)

install(TARGETS LinkPath "${INTERFACE_TARGET}" DESTINATION "${CMAKE_SOURCE_DIR}/lib")