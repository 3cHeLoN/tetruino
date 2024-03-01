#pragma once

#include <string>
#include "tetromino.h"

class TetrominoFactory
{
    public:
        Tetromino create(TetrominoType name);
        Tetromino create_random();
};