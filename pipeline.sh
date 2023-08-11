#!/bin/bash

# Clean
yes | ./clean.sh

# Assemble --> Build --> Test
./assemble.sh && ./build.sh && ./test.sh

