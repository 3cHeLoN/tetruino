#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <random>
#include <map>
#include <chrono>

#include "board.h"
#include "screen_manager.h"
#include "tetromino_factory.h"
#include "tetromino.h"

 typedef std::chrono::high_resolution_clock Clock;
auto lastUpdateTime = Clock::now();

void screenUpdate(ScreenManager &manager, Board &board)
{
    manager.draw(board);
    manager.show();
    lastUpdateTime = Clock::now();
}

// // int main(int argc, char **argv)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    auto board = Board(20, 10);
    auto screen_manager = ScreenManager(10, 20);

    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<int> distr_block(0, 6);
    std::uniform_int_distribution<int> distr_row(0, 20);
    std::uniform_int_distribution<int> distr_col(0, 10);
    int random_integer;

    std::cout << "TETRIS!" << '\n';
    auto factory = new TetrominoFactory();

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

        if (board.check_block(tetromino))
        {
            board.place(tetromino);
        }
        {
            std::cout << "Could not place tetromino " << tetromino.get_type() << '\n';
            std::cout << "At position (" << row << ", " << col << ")" << '\n';
        }
    }

    bool game_over = false;
    SDL_Event e;
    while(!game_over)
    {
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
                case SDL_QUIT:
                    std::cout << "Game OVER" << '\n';
                    game_over = true;
                    break;
            }
        }


        // Screen update.
        auto time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - lastUpdateTime);
        if (time_elapsed.count() >= 16)
        {
            screenUpdate(screen_manager, board);
            std::cout << "Updating screen" << '\n';
        }

        SDL_Delay(10);
    }

    return 0;
}



void game()
{
    bool game_over = false;
    while (!game_over)
    {
    }
}