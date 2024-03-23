#!/bin/bash

echo Testing has started!
echo
for file in ./tests/*.in; do
    echo $file
    ./build/program.elf < $file
    echo
done