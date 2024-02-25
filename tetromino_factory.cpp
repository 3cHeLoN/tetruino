#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <map>

#include "tetromino_factory.h"

const std::map<std::string, std::vector<std::vector<int>>> Tetrominos = {
    {"i", {{1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}},
    {"o", {{1, 1}, {1, 1}}},
    {"t", {{0, 1, 0}, {1, 1, 1}, {0, 0, 0}}},
    {"j", {{1, 0, 0}, {1, 1, 1}, {0, 0, 0}}},
    {"l", {{0, 0, 1}, {1, 1, 1}, {0, 0, 0}}},
    {"s", {{0, 1, 1}, {1, 1, 0}, {0, 0, 0}}},
    {"z", {{1, 1, 0}, {0, 1, 1}, {0, 0, 0}}},
};

TetrominoFactory::TetrominoFactory()
{
}

Tetromino TetrominoFactory::create(std::string name)
{
    std::vector<std::string> tetromino_names = {"i", "o", "t", "j", "l", "s", "z"};

    if (std::find(tetromino_names.begin(), tetromino_names.end(), name) == tetromino_names.end())
    {
        throw std::runtime_error("The tetromino " + name + " does not exist.");
    }

    auto matrix = Matrix<int>(Tetrominos.at(name));
    return Tetromino(matrix);
}