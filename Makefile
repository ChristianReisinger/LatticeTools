SHELL=/bin/bash

CXX=g++
CXXFLAGS=-std=c++11

BIN_DIR=bin/
BUILD_DIR=build/
SRC_DIR=src/
INCLUDE_DIR=include/

OBJ_NAMES=
BIN_NAMES=LatticeTools

OBJS=${OBJ_NAMES:%=${BUILD_DIR}/%.o}
TARGETS=${BIN_NAMES:%=${BIN_DIR}/%}
LIBS=

all: ${TARGETS}

${TARGETS}: ${BIN_DIR}/%: ${SRC_DIR}/%.cc ${OBJS}
	readarray deps < <(depfinder.sh . $<);\
	${CXX} ${CXXFLAGS} -o $@ $^ -I"${INCLUDE_DIR}" "$${deps[@]}" ${LIBS}
	
${OBJS}: ${BUILD_DIR}/%.o: ${SRC_DIR}/%.cc  ${INCLUDE_DIR}/%.hh
	readarray deps < <(depfinder.sh . $<);\
	${CXX} ${CXXFLAGS} -c -o $@ $< -I"${INCLUDE_DIR}" "$${deps[@]}"

clean:
	rm -f ${BIN_DIR}/* ${BUILD_DIR}/*