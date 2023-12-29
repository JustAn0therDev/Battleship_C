#!/bin/sh

clang src/main.c -Werror -Wall -Wunused-variable -o battleship
./battleship