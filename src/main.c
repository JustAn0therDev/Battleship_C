#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers/position.h"
#include "headers/ship.h"
#include "headers/player.h"

const char COLUMNS[COLUMN_SIZE] = { 'A','B','C','D','E','F','G','H','I','J' };
const int ROWS[ROW_SIZE] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

// This function checks if the ship pointer has already been added to the array of ships.
int IsInSeenShips(Ship** seen_ships, Ship* ship);

// This function reads 4 characters from input using fgets. Since this function allocates memory,
// it's return value should be freed after usage.
char* ReadStdinBuffer();

// This function reads the line breaks from the stdin buffer so that
// the fgets function used in ReadStdinBuffer does not read any undesired characters.
void ReadLineBreaksFromStdinBuffer();

// This function checks the "Positions" array for any same positions as (row, column)
int PositionArrayContains(Position* positions, size_t size, int row, char column);

// This function draws the board to stdout with the used positions and
// hit ships.
void DrawBoard(Position* positions, Ship** ships, size_t ships_size);

int main(void) 
{
    Position positions[GRID_SIZE];

    Player* player = CreatePlayer("TestPlayer");

    Ship* seen_ships[MAX_SHIPS];
    
    seen_ships[0] = 0;
    seen_ships[1] = 0;
    seen_ships[2] = 0;
    seen_ships[3] = 0;
    seen_ships[4] = 0;
    
    int seen_ships_idx = 0;
    int pos_idx = 0;

    int final_seen_ships_idx = (player->ships_size - 1);

    while (1)
    {
        system("clear");

        DrawBoard(positions, player->ships, MAX_SHIPS);

        for (size_t i = 0; i < MAX_SHIPS; i++)
        {
            if (IsShipSinked(player->ships[i], positions, GRID_SIZE) == 1)
            {
                if (!IsInSeenShips(seen_ships, player->ships[i]))
                {
                    printf("%s has sinked!\n", player->ships[i]->name);
                    *(seen_ships + seen_ships_idx) = player->ships[i];
                    seen_ships_idx++;
                }
            }
        }

        if (pos_idx == GRID_SIZE || seen_ships_idx > final_seen_ships_idx)
        {
            break;
        }

        char* chosen_position_buffer = ReadStdinBuffer();

        Position chosen_position = (Position){ atoi(&chosen_position_buffer[0]), chosen_position_buffer[2] };

        if (PositionArrayContains(positions, GRID_SIZE, chosen_position.row, chosen_position.column))
        {
            printf("This position has already been used! Press enter to continue.\n");
            getchar();
        }
        else
        {
            positions[pos_idx] = chosen_position;
            pos_idx++;
        }

        free(chosen_position_buffer);

        ReadLineBreaksFromStdinBuffer();
    }

    if (seen_ships_idx == 1)
    {
        puts("Congrats! You've found all ships and won!");
    }

    FreePlayer(player);

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

void DrawBoard(Position* positions, Ship** ships, size_t ships_size)
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
            // e.g. \e[1;31m This is red text \e[0m
            // red=31, green=32
            if (PositionArrayContains(positions, GRID_SIZE, ROWS[i], COLUMNS[j])) 
            {
                int found_ship_in_position = 0;
                
                for (size_t k = 0; k < MAX_SHIPS; k++)
                {
                    if (IsShipInPosition(*(ships + k), ROWS[i], COLUMNS[j]))
                    {
                        printf("\e[1;32mx\e[0m ");
                        found_ship_in_position = 1;
                        break;
                    }
                }

                if (!found_ship_in_position)
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