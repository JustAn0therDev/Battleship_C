#pragma once

#include "headers/position.h"
#include <stdlib.h>

typedef struct ship {
    // NOTES(Ruan): A ship can range from 2 to 5 squares.
    Position* positions;
    size_t size;
    char* name;
    int defeated;
} Ship;

// Checks if the ship has sinked. The ship's positions have to be updated with the player's available positions.
int IsShipSinked(const Ship* ship, const Position* player_positions, const size_t player_positions_size);

// Checks if the ship is in the position (row, column) indicated.
int IsShipInPosition(const Ship* ship, const int row, const int column);

// Creates a ship. This functions returns allocated memory, so call FreeShip after you have finished using it.
Ship* CreateShip(char* name, Position* positions, size_t size);

// Frees all allocated memory for the ship struct.
void FreeShip(Ship* ship);