#!/bin/sh

clang src/main.c src/ship.c src/player.c -Werror -Wall -Wunused-variable -o battleship