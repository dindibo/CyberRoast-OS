#!/bin/bash

rm -f `find -name "*.o" | xargs`

./build.sh && { ./test.sh; } || { ./build.sh && ./test.sh; }
