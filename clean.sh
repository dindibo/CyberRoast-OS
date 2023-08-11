#!/bin/bash

find . -name "*.o" -exec rm {} +

cd src/
make clean
