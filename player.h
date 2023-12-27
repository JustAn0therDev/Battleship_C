#pragma once
#include "position.h";
#include "ship.h";

typedef struct player {
    Position positions[100];
    char* name;
    Ship ships[5];
} Player;