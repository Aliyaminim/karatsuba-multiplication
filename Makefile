CC ?= gcc
QEMU_USER ?= qemu-x86_64
CCFLAGS ?=
VALGRIND_FLAGS ?= --leak-check=yes

BUILD_DIR := build
.DEFAULT_GOAL := program
HEADERS := ./include/karatsuba.h
SRC := karatsuba.c tools.c main.c
OBJS := $(SRC:%.c=$(BUILD_DIR)/%.o)
BIN := program.elf
SRC := ./lib/karatsuba.c ./lib/tools.c ./src/main.c

.PHONY: _build_dir program clean build-docker docker test

_build_dir:
	@mkdir -p ${BUILD_DIR}

program: _build_dir $(OBJS)
	${CC} ${CCFLAGS} ${OBJS} -o ${BUILD_DIR}/$(BIN)

$(BUILD_DIR)/karatsuba.o: $(HEADERS) $(SRC)
	$(CC) $(CCFLAGS) -c ./lib/karatsuba.c -o $@

$(BUILD_DIR)/tools.o: $(HEADERS) $(SRC)
	$(CC) $(CCFLAGS) -c ./lib/tools.c -o $@

$(BUILD_DIR)/main.o: $(HEADERS) $(SRC)
	$(CC) $(CCFLAGS) -c ./src/main.c -o $@

build: program

show: program
	file ${BUILD_DIR}/$(BIN)

run: program
	${BUILD_DIR}/$(BIN)

run-qemu: program
	${QEMU_USER} ${BUILD_DIR}/$(BIN)

gdb: program
	gdb ${BUILD_DIR}/$(BIN)

valgrind: program
	valgrind $(VALGRIND_FLAGS) ${BUILD_DIR}/$(BIN)

build-docker:
	make build CC=${SC_GCC_PATH}/bin/riscv64-unknown-linux-gnu-gcc QEMU_USER=${SC_QEMU_PATH}/qemu-riscv64

run-qemu-docker: build-docker
	echo
	echo "Running in QEMU from Docker..."
	make run-qemu CC=${SC_GCC_PATH}/bin/riscv64-unknown-linux-gnu-gcc QEMU_USER=${SC_QEMU_PATH}/qemu-riscv64 CCFLAGS=-static

docker:
	@docker start $(CONTAINER)
	@docker exec -it $(CONTAINER) bash

clean:
	rm -r ${BUILD_DIR}

test: program
	bash ./tests/testing.sh

