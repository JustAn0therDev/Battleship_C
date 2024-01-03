#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "headers/player.h"
#include "headers/ship.h"
#include "headers/position.h"

Player* CreatePlayer(char* name)
{
    Player* player = malloc(sizeof(Player));

    if (player == 0)
    {
        puts("Unable to allocate memory for player struct.");
        exit(1);
    }

    player->name = malloc(strlen(name));

    if (player->name == 0)
    {
        puts("Unable to allocate memory for player name.");
        exit(1);
    }

    strcpy(player->name, name);

    Position carrier_positions[5];

    carrier_positions[0] = (Position){0,'A'};
    carrier_positions[1] = (Position){0,'B'};
    carrier_positions[2] = (Position){0,'C'};
    carrier_positions[3] = (Position){0,'D'};
    carrier_positions[4] = (Position){0,'E'};

    player->ships[0] = CreateShip("Carrier", carrier_positions, 5);

    return player;
}

void FreePlayer(Player* player)
{
    if (player != 0)
    {
        if (player->name != 0)
        {
            free(player->name);
        }

        for (size_t i = 0; i < 5; i++)
        {
            if (player->ships[i] != 0)
            {
                FreeShip(player->ships[i]);
            }
        }

        free(player);
    }
}