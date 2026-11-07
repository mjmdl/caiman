#!/bin/sh

gcc \
    -o caiman \
    -std=c99 -ggdb -Wall -Wextra -Wpedantic -Werror -Wno-unused-variable -Wno-unused-function \
    source/caiman.c
