#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>

#include "board.h"
#include "screen_manager.h"
#include "tetromino_factory.h"
#include "tetromino.h"


// // int main(int argc, char **argv)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    auto board = new Board(20, 10);
    auto screen_manager = new ScreenManager(20, 10);
    screen_manager->draw(board);
    screen_manager->show();

    std::cout << "TETRIS!" << '\n';
    auto factory = new TetrominoFactory();
    auto tetromino = factory->create(I_block);
    std::cout << "The original block" << '\n';
    tetromino.print();

    std::cout << '\n' << "The rotated block" << '\n';
    tetromino.rotate_clockwise();
    tetromino.print();

    std::cout << '\n' << "The cc  rotated block" << '\n';
    tetromino.rotate_counter_clockwise();
    tetromino.rotate_counter_clockwise();
    tetromino.print();

    return 0;
}



void game()
{
    bool game_over = false;
    while (!game_over)
    {
    }
}