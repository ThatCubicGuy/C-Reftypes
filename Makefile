USING+=System
USING+=System/Collections

# Compiler settings
CC:=gcc
CFLAGS:=-Wall -Iinclude ${USING:%=-Iinclude/%}
OUTPUT:=thing.exe

# Folder settings
BIN:=bin
SRC:=lib
TESTS:=tests

# Library files
LIBSRCS:=$(wildcard ${SRC}/*.c)
LIBOBJS:=${LIBSRCS:${SRC}/%.c=${BIN}/${SRC}/%.o}

# Tests
TESTSRCS:=$(wildcard ${TESTS}/*.c)

test: buildtest runtest

buildtest: ${LIBOBJS}
	${CC} ${CFLAGS} main.c ${TESTSRCS} $(wildcard ${BIN}/${SRC}/*.o) -o ${BIN}/test_${OUTPUT}

runtest:
	${BIN}/test_${OUTPUT}

buildnrun: build run

build: ${LIBOBJS}
	${CC} ${CFLAGS} ${LIBOBJS} -o ${BIN}/${OUTPUT}

run:
	${BIN}/${OUTPUT}

${LIBOBJS}: ${BIN}/lib/%.o: ${SRC}/%.c
	${CC} ${CFLAGS} -c $^ -o $@

clean:
	rm -f ${BIN}/*

cleanlib:
	rm -f ${BIN}/lib/*

debug:
	echo ${LIBOBJS}
	echo ${LIBSRCS}
	mkdir -p ${BIN}
	mkdir -p ${BIN}/${SRC}
