#!/bin/bash

hack_path="/tmp/libcshack"
output_file="libcshack.so"

if [ ! -d $hack_path ]; then
    mkdir $hack_path
fi

clang -Wall -g -m32 -shared -fPIC $(find . -type f -name "*.c" |  tr "\n" " ") -o $hack_path/$output_file -ldl
