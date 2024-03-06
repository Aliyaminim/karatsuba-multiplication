CC ?= gcc
QEMU_USER ?= qemu-x86_64
CCFLAGS ?=


BUILD_DIR := build
DOCKER_CONTAINER_ID := bd9ac9f387e8
.DEFAULT_GOAL := program

.PHONY: _build_dir program clean build-docker docker

_build_dir:
	@mkdir -p ${BUILD_DIR}

program: _build_dir karatsuba.o mpk2.o
	${CC} ${CCFLAGS} ${BUILD_DIR}/karatsuba.o ${BUILD_DIR}/mpk2.o -o ${BUILD_DIR}/program.elf

karatsuba.o: karatsuba.c karatsuba.h
	$(CC) $(CFLAGS) -c karatsuba.c -o ${BUILD_DIR}/karatsuba.o

mpk2.o: mpk2.c karatsuba.h
	$(CC) $(CFLAGS) -c mpk2.c -o ${BUILD_DIR}/mpk2.o

build: program

show: program
	file ${BUILD_DIR}/program.elf

run: program
	${BUILD_DIR}/program.elf

run-qemu: program
	${QEMU_USER} ${BUILD_DIR}/program.elf

run-gdb: CFLAGS+=-g
run-gdb: program
	gdb ${BUILD_DIR}/program.elf

build-docker:
	make build CC=${SC_GCC_PATH}/bin/riscv64-unknown-linux-gnu-gcc QEMU_USER=${SC_QEMU_PATH}/qemu-riscv64

run-qemu-docker: build-docker
	echo
	echo "Running in QEMU from Docker..."
	make run-qemu CC=${SC_GCC_PATH}/bin/riscv64-unknown-linux-gnu-gcc QEMU_USER=${SC_QEMU_PATH}/qemu-riscv64 CCFLAGS=-static

docker:
	@docker start $(DOCKER_CONTAINER_ID)
	@docker exec -it $(DOCKER_CONTAINER_ID) bash

clean:
	rm -r ${BUILD_DIR}

