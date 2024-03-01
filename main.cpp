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

#define INITIAL_REPEAT_MS  30
#define SECOND_REPEAT_MS 8

typedef std::chrono::high_resolution_clock Clock;
auto lastUpdateTime = Clock::now();
bool initialRepeating = false;
bool secondaryRepeating = false;
auto lastKeyRepeat = Clock::now();

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
    bool repeat_condition;
    SDL_Event e;
    while(!game_over)
    {
        auto t1 = Clock::now();
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
                    // First time?
                    if (!initialRepeating && !secondaryRepeating)
                    {
                        initialRepeating = true;
                        lastKeyRepeat = Clock::now();
                    }

                    lastKeyRepeatTime = std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - lastKeyRepeat).count();
                    repeat_condition = (initialRepeating & (lastKeyRepeatTime > INITIAL_REPEAT_MS) || (secondaryRepeating & (lastKeyRepeatTime > SECOND_REPEAT_MS)));
                    if (repeat_condition)
                    {
                        std::cout << "Repeating, last time " << lastKeyRepeatTime << '\n';
                        initialRepeating = false;
                        lastKeyRepeat = Clock::now();
                        switch (e.key.keysym.sym) {
                            case SDLK_DOWN:
                                printf("Go down!\n");
                                game.move_down();
                                break;
                            case SDLK_LEFT:
                                printf("Left key pressed!\n");
                                game.move_left();
                                break;
                            case SDLK_RIGHT:
                                printf("Right key pressed!\n");
                                game.move_right();
                                break;
                            default:
                                break;
                        }
                    }
                    else
                    {
                        switch (e.key.keysym.sym) {
                            case SDLK_UP:
                            case SDLK_s:
                                printf("Go down!\n");
                                game.rotate(true);
                                break;
                            case SDLK_a:
                                printf("Go down!\n");
                                game.rotate(false);
                                break;
                            case SDLK_DOWN:
                                printf("Go down!\n");
                                game.move_down();
                                break;
                            case SDLK_LEFT:
                                printf("Left key pressed!\n");
                                game.move_left();
                                break;
                            case SDLK_RIGHT:
                                printf("Right key pressed!\n");
                                game.move_right();
                                break;
                            default:
                                break;
                        }
                    }
                    break;
                case SDL_KEYUP:
                    std::cout << "Key up" << '\n';
                    initialRepeating = false;
                    secondaryRepeating = false;
                    break;
                default:
                    break;
            }
        }

        auto t2 = Clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
        if (duration.count() > 10)
        {
            std::cout << "Input handling took " << duration.count() << " milliseconds" << '\n';
        }

        // Screen update.
        auto time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - lastUpdateTime);
        if (time_elapsed.count() >= 1)
        {
            // TODO: Should this be updated more frequently?
            auto t1 = Clock::now();
            game_over = !game.update();
            screen_manager.draw(game.board);
            screen_manager.draw(game.tetromino);
            screen_manager.show();
            auto t2 = Clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1);

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