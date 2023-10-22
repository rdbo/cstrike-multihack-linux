#!/bin/sh

mkdir -p build
docker build -t ronix .
docker run -v "$(pwd)/build:/app/build" -it ronix
