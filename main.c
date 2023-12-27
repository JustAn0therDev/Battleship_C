#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "position.h"

const short GRID_SIZE = 10;

const char COLUMNS[GRID_SIZE] = { 'A','B','C','D','E','F','G','H','I','J' };
const int ROWS[GRID_SIZE] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

// I'll need a list of attacked positions in the board and 
// a struct for both players.
// If a player has lost a ship, for example, I'd like to draw the board in a 
// different color as a feedback to the other player that there was a ship.
// That way, both players can know where they hit each other's ships and
// make a plan based on that.

// Available square grids are represented by the unicode character "◯" and
// unavailable ones by "x".

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
            // TODO(Ruan): to draw characters in another color, just pass in the 
            // color command, insert the characters to draw and go back to the default color.
            // \e[1;31m This is red text \e[0m
            // red=31, green=32
            printf("◯ ");
        }

        printf("\n");
    }
}

int main(void) 
{
    Position pos[100];

    pos[0] = (Position){ 0, 'A' };

    DrawBoard(pos);
    return 0;
}