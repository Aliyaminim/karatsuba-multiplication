# Karatsuba fast multiplication algorithm

### Task

Product two polynomials using the karatsuba algorithm

https://en.wikipedia.org/wiki/Karatsuba_algorithm

## How to build on host machine
```bash
git clone https://github.com/Aliyaminim/karatsuba-multiplication.git
cd karatsuba-multiplication
make program CC=[] CCFLAGS=[] 
```

## How to run the program
```bash
./build/program.elf < [file]
```

## How to test the program
```bash
make test
```
## How to run gdb
```bash
make clean
make program CC=[] CCFLAGS+=-g
gdb ./build/program.elf < [file]
```
## How to run valgrind
```bash
valgrind VALGRIND_FLAGS+=[] ./build/program.elf < [file]
```
## How to build application inside docker
```bash
source /opt/sc-dt/env.sh 
make build-docker
```

Additionally, to run application on qemu inside docker:
```bash
make run-qemu-docker 
```

