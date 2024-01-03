#include "headers/ship.h"
#include "headers/position.h"
#include <string.h>
#include <stdio.h>

int IsShipSinked(const Ship* ship, const Position* player_positions, const size_t player_positions_size)
{
    if (ship == 0) 
    {
        return 0;
    }
    
    size_t ship_positions = ship->size;

    for (size_t i = 0; i < ship->size; i++)
    {
        for (size_t j = 0; j < player_positions_size; j++)
        {
            if (ship->positions[i].row == player_positions[j].row && ship->positions[i].column == player_positions[j].column)
            {
                ship_positions--;
                break;
            }
        }
    }

    return ship_positions == 0;
}

int IsShipInPosition(const Ship* ship, const int row, const int column)
{
    if (ship == 0) return 0;

    for (size_t i = 0; i < ship->size; i++)
    {
        if (ship->positions[i].column == column && ship->positions[i].row == row)
        {
            return 1;
        }
    }

    return 0;
}

Ship *CreateShip(char *name, Position *positions, size_t size)
{
    Ship* ship = malloc(sizeof(Ship));
    
    if (ship == 0) 
    {
        puts("Unable to allocate memory for ship.");
        exit(1);
    }

    ship->name = malloc(sizeof(char) * strlen(name));
    strcpy(ship->name, name);

    ship->positions = malloc(sizeof(Position) * size);

    if (ship->positions == 0)
    {
        puts("Unable to allocate memory for ship positions.");
        exit(1);
    }

    memcpy(ship->positions, positions, sizeof(Position) * size);

    ship->size = size;

    return ship;
}

void FreeShip(Ship *ship)
{
    if (ship != 0)
    {
        if (ship->name != 0)
        {
            free(ship->name);
        }

        if (ship->positions != 0)
        {
            free(ship->positions);
        }

        free(ship);
    }
}