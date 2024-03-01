#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <random>
#include <map>

#include "color.h"
#include "tetromino.h"
#include "tetromino_factory.h"

std::map<int, TetrominoType> tetromino_type_from_index
{
    {0, I_block},
    {1, O_block},
    {2, T_block},
    {3, J_block},
    {4, L_block},
    {5, S_block},
    {6, Z_block},
};

Tetromino TetrominoFactory::create(TetrominoType type)
{
    auto tetromino = Tetromino(type);
    tetromino.set_color(colormap.at(type));
    return tetromino;
}

Tetromino TetrominoFactory::create_random()
{
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<int> tetromino_distribution(0, 6);
    auto tetromino_index = tetromino_distribution(eng);
    auto tetromino_type = tetromino_type_from_index.at(tetromino_index);
    return create(tetromino_type);
}