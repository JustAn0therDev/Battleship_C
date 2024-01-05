#pragma once

#include "position.h"
#include "ship.h"
#include "constants.h"

typedef struct player {
    Position positions[100];
    char* name;
    size_t ships_size;
    Ship* ships[MAX_SHIPS];
} Player;

// This function creates a player object.
Player* CreatePlayer(char* name);

// This function frees a player object.
void FreePlayer(Player* player);