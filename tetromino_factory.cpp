#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <map>

#include "tetromino_factory.h"

const std::map<TetrominoType, std::vector<Matrix<int>>> Tetrominos = {
    {I_block, {
        Matrix<int>({{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}}),
        Matrix<int>({{0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}}),
        Matrix<int>({{0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}}),
        Matrix<int>({{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}}),
    }},
    {O_block, {
        Matrix<int>({{1, 1}, {1, 1}}),
        Matrix<int>({{1, 1}, {1, 1}}),
        Matrix<int>({{1, 1}, {1, 1}}),
        Matrix<int>({{1, 1}, {1, 1}}),
    }},
    {T_block, {
        Matrix<int>({{0, 1, 0}, {1, 1, 1}, {0, 0, 0}}),
        Matrix<int>({{0, 1, 0}, {0, 1, 1}, {0, 1, 0}}),
        Matrix<int>({{0, 0, 0}, {1, 1, 1}, {0, 1, 0}}),
        Matrix<int>({{0, 1, 0}, {1, 1, 0}, {0, 1, 0}}),
    }},
    {J_block, {
        Matrix<int>({{1, 0, 0}, {1, 1, 1}, {0, 0, 0}}),
        Matrix<int>({{0, 1, 0}, {0, 1, 0}, {0, 1, 1}}),
        Matrix<int>({{0, 0, 0}, {1, 1, 1}, {1, 0, 0}}),
        Matrix<int>({{1, 1, 0}, {0, 1, 0}, {1, 1, 0}}),
    }},
    {L_block, {
        Matrix<int>({{0, 0, 1}, {1, 1, 1}, {0, 0, 0}}),
        Matrix<int>({{0, 1, 0}, {0, 1, 0}, {0, 1, 1}}),
        Matrix<int>({{0, 0, 0}, {1, 1, 1}, {1, 0, 0}}),
        Matrix<int>({{1, 1, 0}, {0, 1, 0}, {0, 1, 0}}),
    }},
    {S_block, {
        Matrix<int>({{0, 1, 1}, {1, 1, 0}, {0, 0, 0}}),
        Matrix<int>({{0, 1, 0}, {0, 1, 1}, {0, 0, 1}}),
        Matrix<int>({{0, 0, 0}, {0, 1, 1}, {1, 1, 0}}),
        Matrix<int>({{1, 0, 0}, {1, 1, 0}, {1, 0, 0}}),
    }},
    {Z_block, {
        Matrix<int>({{1, 1, 0}, {0, 1, 1}, {0, 0, 0}}),
        Matrix<int>({{0, 0, 1}, {0, 1, 1}, {0, 1, 0}}),
        Matrix<int>({{0, 0, 0}, {1, 1, 0}, {0, 1, 1}}),
        Matrix<int>({{0, 1, 0}, {1, 1, 0}, {1, 0, 0}}),
    }},
};

Tetromino TetrominoFactory::create(TetrominoType type)
{
    int rotation = 0;
    return Tetromino(Tetrominos.at(type));
}