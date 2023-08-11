#!/bin/bash

docker run --rm -v /share/source/os-dev/src/:/src kevincharm/i686-elf-gcc-toolchain:5.5.0 bash -c 'cd /src/; make'
