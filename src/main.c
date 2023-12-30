#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/position.h"
#include "headers/ship.h"

const short GRID_SIZE = 10;
const short MAX_INPUT_SIZE = 4;
const char COLUMNS[GRID_SIZE] = { 'A','B','C','D','E','F','G','H','I','J' };
const int ROWS[GRID_SIZE] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

// This function reads 4 characters from input using fgets.
char* ReadStdinBuffer()
{
    char* buffer = malloc(sizeof(char) * MAX_INPUT_SIZE);
    fgets(buffer, MAX_INPUT_SIZE, stdin);

    return buffer;
}

// This function reads the line breaks from the stdin buffer so that
// the fgets function used in ReadStdinBuffer does not read any undesired characters.
void ReadLineBreaksFromStdinBuffer()
{
    char c;
    while ((c = getchar()) != '\n') {}
}

int PositionArrayContains(Position* pos, size_t size, int row, char column)
{
    for (size_t i = 0; i < size; i++)
    {
        if (pos[i].row == row && pos[i].column == column)
        {
            return 1;
        }
    }

    return 0;
}

void DrawBoard(Position* pos, Ship* ship)
{
    // NOTES(Ruan): making space for the indicators.
    printf("  ");

    for (int i = 0; i < GRID_SIZE; i++)
    {
        printf("%c ", COLUMNS[i]);
    }

    printf("\n");

    for (int i = 0; i < GRID_SIZE; i++)
    {
        printf("%i ", ROWS[i]);

        for (int j = 0; j < GRID_SIZE; j++)
        {
            // NOTES(Ruan): to draw characters in another color, just pass in the 
            // color command, insert the characters to draw and go back to the default color.
            // \e[1;31m This is red text \e[0m
            // red=31, green=32

            if (PositionArrayContains(pos, GRID_SIZE, ROWS[i], COLUMNS[j])) 
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

    if (IsShipSinked(ship, pos, GRID_SIZE * GRID_SIZE))
    {
        printf("%s has sinked!\n", ship->name);
    }
}

int main(void) 
{
    Position pos[100];

    Position ship_positions[2];

    *ship_positions = (Position){ 0, 'A' };
    *(ship_positions + 1) = (Position){ 0, 'B' };

    Ship *ship = CreateShip("Destroyer", ship_positions, 2);

    int pos_idx = 0;

    while (pos_idx <= 100)
    {
        DrawBoard(pos, ship);

        char* buffer = ReadStdinBuffer();

        pos[pos_idx] = (Position){ atoi(&buffer[0]), buffer[2] };

        pos_idx++;

        free(buffer);

        ReadLineBreaksFromStdinBuffer();
    }
    
    FreeShip(ship);
    
    return 0;
}