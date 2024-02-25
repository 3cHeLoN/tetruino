#include <iostream>
#include <vector>
#include <string>

#include "tetromino_factory.h"
#include "tetromino.h"


int main()
{
    auto factory = new TetrominoFactory();
    auto tetromino = factory->create(T_block);
    tetromino.m_matrix.print();
}



void game()
{
    bool game_over = false;
    while (!game_over)
    {
    }
}