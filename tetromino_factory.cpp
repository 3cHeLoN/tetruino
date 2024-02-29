#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <map>

#include "color.h"
#include "tetromino.h"
#include "tetromino_factory.h"

Tetromino TetrominoFactory::create(TetrominoType type)
{
    int rotation = 0;
    auto tetromino = Tetromino(type);
    tetromino.set_color(colormap.at(type));
    return tetromino;
}