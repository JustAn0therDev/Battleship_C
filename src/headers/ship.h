#pragma once
#include "headers/position.h"
#include <stdlib.h>

typedef struct ship {
    // NOTES(Ruan): A ship can range from 2 to 5 squares.
    Position* pos;
    size_t pos_size;
    char* name;
    int defeated;
} Ship;