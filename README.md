# Karatsuba fast multiplication algorithm

### Task

Product two polynomials using the karatsuba algorithm

https://en.wikipedia.org/wiki/Karatsuba_algorithm

## How to clone
```bash
git clone https://github.com/Aliyaminim/karatsuba-multiplication.git
cd karatsuba-multiplication
```

## How to build application inside docker
```bash
make docker
cd ./programming/c_grad/karatsuba-multiplication/
source /opt/sc-dt/env.sh 
make build-docker
```

Additionally, to run application on qemu inside docker:
```bash
make run-qemu-docker 
```
