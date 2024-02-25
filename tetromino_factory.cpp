#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <map>

#include "tetromino_factory.h"

const std::map<TetrominoType, std::vector<std::vector<int>>> Tetrominos = {
    {I_block, {{1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}},
    {O_block, {{1, 1}, {1, 1}}},
    {T_block, {{0, 1, 0}, {1, 1, 1}, {0, 0, 0}}},
    {J_block, {{1, 0, 0}, {1, 1, 1}, {0, 0, 0}}},
    {L_block, {{0, 0, 1}, {1, 1, 1}, {0, 0, 0}}},
    {S_block, {{0, 1, 1}, {1, 1, 0}, {0, 0, 0}}},
    {Z_block, {{1, 1, 0}, {0, 1, 1}, {0, 0, 0}}},
};

TetrominoFactory::TetrominoFactory()
{
}

Tetromino TetrominoFactory::create(TetrominoType type)
{
    auto matrix = Matrix<int>(Tetrominos.at(type));
    return Tetromino(matrix);
}