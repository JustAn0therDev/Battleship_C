#!/bin/sh

clang src/main.c src/ship.c -Werror -Wall -Wunused-variable -o battleship
./battleship