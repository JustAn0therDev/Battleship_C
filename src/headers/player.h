#pragma once
#include "headers/position.h";
#include "headers/ship.h";

typedef struct player {
    Position positions[100];
    char* name;
    Ship ships[5];
} Player;