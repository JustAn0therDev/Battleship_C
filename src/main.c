#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/position.h"
#include "headers/ship.h"

const short GRID_SIZE = 100;
const short ROW_SIZE = 10;
const short COLUMN_SIZE = 10;
const short MAX_INPUT_SIZE = 4;
const char COLUMNS[COLUMN_SIZE] = { 'A','B','C','D','E','F','G','H','I','J' };
const int ROWS[ROW_SIZE] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

// This function checks if the ship pointer has already been added to the array of ships.
int IsInSeenShips(Ship** seen_ships, Ship* ship);

// This function reads 4 characters from input using fgets. Since this function allocates memory,
// it should be freed after usage.
char* ReadStdinBuffer();

// This function reads the line breaks from the stdin buffer so that
// the fgets function used in ReadStdinBuffer does not read any undesired characters.
void ReadLineBreaksFromStdinBuffer();

// This function checks the "Positions" array for any same positions as (row, column)
int PositionArrayContains(Position* positions, size_t size, int row, char column);

void DrawBoard(Position* positions, Ship* ship)
{
    // NOTES(Ruan): making space for the indicators.
    printf("  ");

    for (int i = 0; i < COLUMN_SIZE; i++)
    {
        printf("%c ", COLUMNS[i]);
    }

    printf("\n");

    for (int i = 0; i < ROW_SIZE; i++)
    {
        printf("%i ", ROWS[i]);

        for (int j = 0; j < COLUMN_SIZE; j++)
        {
            // NOTES(Ruan): to draw characters in another color, just pass in the 
            // color command, insert the characters to draw and go back to the default color.
            // \e[1;31m This is red text \e[0m
            // red=31, green=32

            if (PositionArrayContains(positions, GRID_SIZE, ROWS[i], COLUMNS[j])) 
            {
                if (IsShipInPosition(ship, ROWS[i], COLUMNS[j]))
                {
                    printf("\e[1;32mx\e[0m ");
                }
                else
                {
                    printf("\e[1;31mx\e[0m ");
                }
                
                continue;
            }

            printf("◯ ");
        }

        printf("\n");
    }
}

int main(void) 
{
    Position positions[GRID_SIZE];

    Position ship_positions[2];

    *ship_positions = (Position){ 0, 'A' };
    *(ship_positions + 1) = (Position){ 0, 'B' };

    Ship *ship = CreateShip("Destroyer", ship_positions, 2);

    Ship* seen_ships[5];
    
    seen_ships[0] = 0;
    seen_ships[1] = 0;
    seen_ships[2] = 0;
    seen_ships[3] = 0;
    seen_ships[4] = 0;
    
    int seen_ships_idx = 0;
    int pos_idx = 0;

    // TODO(Ruan): this check is temporary. It'll later check for
    // the amount of ships available on each player's side.
    while (pos_idx <= GRID_SIZE)
    {
        system("clear");

        DrawBoard(positions, ship);

        if (IsShipSinked(ship, positions, GRID_SIZE))
        {
            if (!IsInSeenShips(seen_ships, ship))
            {
                printf("%s has sinked!\n", ship->name);
                *(seen_ships + seen_ships_idx) = ship;
                seen_ships_idx++;
            }
        }

        char* chosen_position_buffer = ReadStdinBuffer();

        positions[pos_idx] = (Position){ atoi(&chosen_position_buffer[0]), chosen_position_buffer[2] };

        pos_idx++;

        free(chosen_position_buffer);

        ReadLineBreaksFromStdinBuffer();
    }
    
    FreeShip(ship);
    
    return 0;
}

int IsInSeenShips(Ship** seen_ships, Ship* ship)
{
    int seen_ships_idx = 0;

    while (*(seen_ships + seen_ships_idx) != 0)
    {
        if (*(seen_ships + seen_ships_idx) == ship)
        {
            return 1;
        }

        seen_ships_idx++;
    }

    return 0;
}

char* ReadStdinBuffer()
{
    char* buffer = malloc(sizeof(char) * MAX_INPUT_SIZE);
    fgets(buffer, MAX_INPUT_SIZE, stdin);

    return buffer;
}

void ReadLineBreaksFromStdinBuffer()
{
    char c;
    while ((c = getchar()) != '\n') {}
}

int PositionArrayContains(Position* positions, size_t size, int row, char column)
{
    for (size_t i = 0; i < size; i++)
    {
        if (positions[i].row == row && positions[i].column == column)
        {
            return 1;
        }
    }

    return 0;
}