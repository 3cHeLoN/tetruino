#pragma once

#include <random>
#include <string>

#include "tetromino.h"

class TetrominoFactory
{
private:
  Tetromino current_block;
  Tetromino next_block;
  std::mt19937 random_engine;
  std::uniform_int_distribution<int> tetromino_distribution;

public:
  TetrominoFactory();
  Tetromino create(TetrominoType name);
  Tetromino create_random();
  Tetromino get_block();
  Tetromino the_next_block() { return next_block; };
};