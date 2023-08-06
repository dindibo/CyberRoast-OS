#!/bin/bash

./build.sh && { ./test.sh; } || { ./build.sh && ./test.sh; }
