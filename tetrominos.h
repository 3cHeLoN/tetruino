#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <string>

static const std::map<std::string, std::vector<std::vector<int>>> Tetrominos = {
    {"i", {{1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}},
    {"o", {{1, 1}, {1, 1}}},
    {"t", {{0, 1, 0}, {1, 1, 1}, {0, 0, 0}}},
    {"j", {{1, 0, 0}, {1, 1, 1}, {0, 0, 0}}},
    {"l", {{0, 0, 1}, {1, 1, 1}, {0, 0, 0}}},
    {"s", {{0, 1, 1}, {1, 1, 0}, {0, 0, 0}}},
    {"z", {{1, 1, 0}, {0, 1, 1}, {0, 0, 0}}},
};
