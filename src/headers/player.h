#pragma once

#include "position.h"
#include "ship.h"

typedef struct player {
    Position positions[100];
    char* name;
    Ship* ships[5];
} Player;

// This function creates a player object.
Player* CreatePlayer(char* name);

// This function frees a player object.
void FreePlayer(Player* player);