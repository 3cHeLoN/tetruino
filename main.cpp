#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <random>
#include <map>
#include <chrono>

#include "board.h"
#include "game.h"
#include "screen_manager.h"
#include "tetromino_factory.h"
#include "tetromino.h"

#define REPEAT_MS 50
#define INITIAL_REPEAT_MS  300

typedef std::chrono::high_resolution_clock Clock;
auto lastUpdateTime = Clock::now();
auto lastKeyRepeat = Clock::now();

bool DOWN_PRESSED = false;
bool LEFT_PRESSED = false;
bool RIGHT_PRESSED = false;
bool UP_PRESSED = false;
bool S_PRESSED = false;
bool A_PRESSED = false;

// // int main(int argc, char **argv)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    auto screen_manager = ScreenManager(10, 20);
    auto game = Game();
    std::cout << "TETRIS!" << '\n';

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

    bool game_over = false;
    int lastKeyRepeatTime;
    bool repeat, keypressed = false;
    bool firstpress = true;
    auto repeat_ms = INITIAL_REPEAT_MS;
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
                case SDL_KEYDOWN:
                    if (e.key.repeat > 0)
                    {
                        break;
                    }
                    std::cout << "KEY DOWN" << '\n';
                    keypressed = true;

                    switch (e.key.keysym.sym)
                    {
                        case SDLK_UP:
                            std::cout << "UP KEY" << '\n';
                            UP_PRESSED = true;
                            break;
                        case SDLK_DOWN:
                            std::cout << "DOWN KEY" << '\n';

                            DOWN_PRESSED = true;
                            break;
                        case SDLK_LEFT:
                            std::cout << "LEFT KEY" << '\n';

                            LEFT_PRESSED = true;
                            break;
                        case SDLK_RIGHT:
                            std::cout << "RIGHT KEY" << '\n';

                            RIGHT_PRESSED = true;
                            break;
                        case SDLK_a:
                            A_PRESSED = true;
                            break;
                        case SDLK_s:
                            S_PRESSED = true;
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    repeat = false;
                    keypressed = false;
                    A_PRESSED = false;
                    S_PRESSED = false;
                    UP_PRESSED = false;
                    DOWN_PRESSED = false;
                    LEFT_PRESSED = false;
                    RIGHT_PRESSED = false;
                    firstpress = true;
                    repeat_ms = INITIAL_REPEAT_MS;
                    break;
            }
        }

        if (keypressed)
        {
            // Handle non-repeatable keys first:
            if (UP_PRESSED | S_PRESSED)
            {
                game.rotate(true);
                UP_PRESSED = false;
                S_PRESSED = false;
            }
            if (A_PRESSED)
            {
                game.rotate(false);
                A_PRESSED = false;
            }

            auto polltime = Clock::now();
            auto time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(polltime - lastKeyRepeat);
            if (time_elapsed.count() > repeat_ms || firstpress)
            {
                lastKeyRepeat = polltime;

                if (!firstpress)
                {
                    repeat_ms = REPEAT_MS;
                }
                if (LEFT_PRESSED)
                {
                    game.move_left();
                }
                if (RIGHT_PRESSED)
                {
                    game.move_right();
                }
                if (DOWN_PRESSED)
                {
                    game.move_down();
                }
                firstpress = false;
            }
        }

        // Screen update.
        auto time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - lastUpdateTime);
        if (time_elapsed.count() >= 1)
        {
            // TODO: Should this be updated more frequently?
            game_over = !game.update();
            screen_manager.draw(game.board);
            screen_manager.draw(game.tetromino);
            screen_manager.show();
            
            lastUpdateTime = Clock::now();
        }

        SDL_Delay(1);
    }

    std::cout << "GAME OVER!!!" << '\n';
    return 0;
}



void game()
{
    bool game_over = false;
    while (!game_over)
    {
    }
}