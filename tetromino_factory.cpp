#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <map>

#include "color.h"
#include "tetromino.h"
#include "tetromino_factory.h"

std::map<int, TetrominoType> tetromino_type_from_index{
    {0, I_block},
    {1, O_block},
    {2, T_block},
    {3, J_block},
    {4, L_block},
    {5, S_block},
    {6, Z_block},
};

TetrominoFactory::TetrominoFactory() : random_engine(std::random_device{}()), tetromino_distribution(0, 6)
{
}

Tetromino TetrominoFactory::create(TetrominoType type)
{
  auto tetromino = Tetromino(type);
  tetromino.set_color(colormap.at(type));
  return tetromino;
}

Tetromino TetrominoFactory::create_random()
{
  auto tetromino_index = tetromino_distribution(random_engine);
  std::cout << "Generating tetromino of index " << tetromino_index << '\n';
  auto tetromino_type = tetromino_type_from_index.at(tetromino_index);
  return create(tetromino_type);
}

Tetromino TetrominoFactory::get_block()
{
  current_block = next_block;
  current_block.rotate(ClockWise);
  next_block = create_random();
  next_block.rotate(CounterClockWise);
  return current_block;
}