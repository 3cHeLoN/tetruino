#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <random>
#include <map>

#include "board.h"
#include "screen_manager.h"
#include "tetromino_factory.h"
#include "tetromino.h"


// // int main(int argc, char **argv)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    auto board = new Board(20, 10);
    auto screen_manager = new ScreenManager(10, 20);

    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<int> distr_block(0, 6);
    std::uniform_int_distribution<int> distr_row(0, 20);
    std::uniform_int_distribution<int> distr_col(0, 10);
    int random_integer;

    std::cout << "TETRIS!" << '\n';
    auto factory = new TetrominoFactory();
    auto tetromino = factory->create(I_block);
    std::cout << "The original block" << '\n';
    tetromino.print();

    std::map<int, TetrominoType> tetrindex =
    {
        {0, I_block},
        {1, O_block},
        {2, T_block},
        {3, J_block},
        {4, L_block},
        {5, S_block},
        {6, Z_block},
    };

    for (int i = 0; i < 20; i++)
    {
        random_integer = distr_block(eng);
        auto tetromino = factory->create(tetrindex.at(random_integer));

        auto row = distr_row(eng);
        auto col = distr_col(eng);
        tetromino.set_position(row, col);

        if (board->check_block(tetromino))
        {
            board->place(tetromino);
        }
        {
            std::cout << "Could not place tetromino " << tetromino.get_type() << '\n';
            std::cout << "At position (" << row << ", " << col << ")" << '\n';
        }
    }
    
    screen_manager->draw(board);
    screen_manager->show();

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