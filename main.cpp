#include <iostream>
#include <vector>
#include <string>

#include "tetromino_factory.h"
#include "tetromino.h"


int main()
{
    std::cout << "TETRIS!" << '\n';
    auto factory = new TetrominoFactory();
    auto tetromino = factory->create(T_block);
    std::cout << "The original block" << '\n';
    tetromino.print();

    std::cout << '\n' << "The rotated block" << '\n';
    tetromino.rotate_clockwise();
    tetromino.print();

std::cout << '\n' << "Thecc  rotated block" << '\n';
    tetromino.rotate_counter_clockwise();
    tetromino.rotate_counter_clockwise();
    tetromino.print();
}



void game()
{
    bool game_over = false;
    while (!game_over)
    {
    }
}