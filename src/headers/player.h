#pragma once

#include "position.h"
#include "ship.h"

typedef struct player {
    Position positions[100];
    char* name;
    size_t ships_size;
    Ship* ships[];
} Player;

// This function creates a player object.
Player* CreatePlayer(char* name);

// This function frees a player object.
void FreePlayer(Player* player);