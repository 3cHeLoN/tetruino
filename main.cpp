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

#define INITIAL_REPEAT_MS  40
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
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
                case SDL_QUIT:
                    std::cout << "Game OVER" << '\n';
                    game_over = true;
                    break;
                case SDL_KEYDOWN:
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
                    break;
                case SDL_KEYUP:
                    std::cout << "Key up" << '\n';
                    // Before repeat?
                    if (!secondaryRepeating)
                    {
                        switch (e.key.keysym.sym) {
                            case SDLK_UP:
                            case SDLK_s:
                                printf("Rotate!\n");
                                game.rotate(true);
                                break;
                            case SDLK_a:
                                game.rotate(false);
                                break;
                            case SDLK_DOWN:
                                printf("Go down!\n");
                                game.move_down();
                                break;
                            case SDLK_LEFT:
                                printf("Go left!\n");
                                game.move_left();
                                break;
                            case SDLK_RIGHT:
                                printf("Go right!\n");
                                game.move_right();
                                break;
                            default:
                                break;
                        }
                    }
                    initialRepeating = false;
                    secondaryRepeating = false;
                    break;
                default:
                    break;
            }
        }

        // Screen update.
        auto time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - lastUpdateTime);
        if (time_elapsed.count() >= 16)
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