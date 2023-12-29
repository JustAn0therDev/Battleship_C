#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/position.h"

const short GRID_SIZE = 10;

const char COLUMNS[GRID_SIZE] = { 'A','B','C','D','E','F','G','H','I','J' };
const int ROWS[GRID_SIZE] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

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

void DrawBoard(Position* pos)
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

            // TODO(Ruan): If a ship is in a position, draw it with a green "x"
            // A feedback that the position has already been hit and contains a ship.
            if (PositionArrayContains(pos, GRID_SIZE, ROWS[i], COLUMNS[j])) {
                printf("\e[1;31mx\e[0m ");
                continue;
            }

            printf("\e[1;32m◯ \e[0m");
        }

        printf("\n");
    }
}

int main(void) 
{
    Position pos[100];

    pos[0] = (Position){ 0, 'A', 0 }; // Row, column, shot
    pos[1] = (Position){ 4, 'F', 1 }; // Row, column, shot

    DrawBoard(pos);
    return 0;
}