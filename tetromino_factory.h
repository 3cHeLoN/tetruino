#pragma once

#include <string>
#include "tetromino.h"

class TetrominoFactory
{
    public:
        TetrominoFactory();
        Tetromino create(TetrominoType name);
};