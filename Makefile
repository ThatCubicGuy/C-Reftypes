USING+=System
USING+=System/Collections

# Default rule

test: buildtest runtest

# Compiler settings
CC:=clang
CFLAGS:=-Wno-microsoft-anon-tag -fms-extensions -std=gnu23 -Wall -Iinclude ${USING:%=-Iinclude/%}
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


# Helper for making rules for each file separately.
SEPARATE_BUILD:=$(wildcard *.c) $(wildcard */*.c) $(wildcard */*/*.c)
# A "Function" for getting the actual basename of the current rule.
nameof=$(basename $(notdir ${@}))
# Making separate files (for testing with uncompilable lib)
${SEPARATE_BUILD}: %: void
	${CC} ${CFLAGS} ${@} -o ${BIN}/$(nameof).exe && ${BIN}/$(nameof).exe

void:

# .PHONY: ${SEPARATE_BUILD}

clean:
	rm -f ${BIN}/*

cleanlib:
	rm -f ${BIN}/lib/*

debug:
# 	echo ${LIBOBJS}
# 	echo ${LIBSRCS}
	echo $(basename $(notdir ${SEPARATE_BUILD}))
	mkdir -p ${BIN}
	mkdir -p ${BIN}/${SRC}

cc:
	${CC} --version