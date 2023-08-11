#!/bin/bash

# Clean
yes | ./clean.sh

# Assemble --> Build --> Test
./assemble.sh && ./build2.sh && ./test.sh

