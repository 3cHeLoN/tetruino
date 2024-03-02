#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <map>
#include <chrono>

#include "board.h"
#include "game.h"
#include "screen_manager.h"
#include "tetromino_factory.h"
#include "tetromino.h"

#define REPEAT_MS 50
#define INITIAL_REPEAT_MS  250

typedef std::chrono::high_resolution_clock Clock;
auto lastUpdateTime = Clock::now();
auto lastKeyRepeat = Clock::now();
auto game_start = Clock::now();
int repaints = 0;

bool DOWN_PRESSED = false;
bool LEFT_PRESSED = false;
bool RIGHT_PRESSED = false;
bool UP_PRESSED = false;
bool S_PRESSED = false;
bool A_PRESSED = false;

void unset_keys()
{
    DOWN_PRESSED = false;
    LEFT_PRESSED = false;
    RIGHT_PRESSED = false;
    UP_PRESSED = false;
    S_PRESSED = false;
    A_PRESSED = false;
}

int number_of_pressed_keys()
{
    return DOWN_PRESSED + LEFT_PRESSED + RIGHT_PRESSED + UP_PRESSED + S_PRESSED + A_PRESSED;
}

int main(int argc, char **argv)
{
    auto screen_manager = ScreenManager(10, 20);
    auto game = Game();
    std::cout << "TETRIS!" << '\n';

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
                    game_over = true;
                    break;
                case SDL_KEYDOWN:
                    if (e.key.repeat > 0)
                    {
                        break;
                    }
                    std::cout << "Key pressed" << '\n';
                    keypressed = true;

                    switch (e.key.keysym.sym)
                    {
                        case SDLK_UP:
                            UP_PRESSED = true;
                            break;
                        case SDLK_DOWN:

                            DOWN_PRESSED = true;
                            break;
                        case SDLK_LEFT:

                            LEFT_PRESSED = true;
                            break;
                        case SDLK_RIGHT:

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
                    std::cout << "Key released" << '\n';

                    switch (e.key.keysym.sym)
                    {
                        case SDLK_UP:
                            UP_PRESSED = false;
                            break;
                        case SDLK_DOWN:

                            DOWN_PRESSED = false;
                            break;
                        case SDLK_LEFT:

                            LEFT_PRESSED = false;
                            break;
                        case SDLK_RIGHT:

                            RIGHT_PRESSED = false;
                            break;
                        case SDLK_a:
                            A_PRESSED = false;
                            break;
                        case SDLK_s:
                            S_PRESSED = false;
                            break;
                    }
                    
                    if (number_of_pressed_keys() == 0)
                    {
                        repeat = false;
                        keypressed = false;
                        firstpress = true;
                        repeat_ms = INITIAL_REPEAT_MS;
                    }
                    break;
            }
        }

        if (keypressed)
        {
            // Handle non-repeatable keys first:
            if (UP_PRESSED | S_PRESSED)
            {
                game.rotate(ClockWise);
                UP_PRESSED = false;
                S_PRESSED = false;
            }
            if (A_PRESSED)
            {
                game.rotate(CounterClockWise);
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
                    game.move(DirectionLeft);
                }
                if (RIGHT_PRESSED)
                {
                    game.move(DirectionRight);
                }
                if (DOWN_PRESSED)
                {
                    game.move(DirectionDown);
                }
                firstpress = false;
            }
        }

        // Screen update.
        auto time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - lastUpdateTime);
        if (time_elapsed.count() >= 1)
        {
            // TODO: Should this be updated more frequently?
            auto success = game.update();
            if (!success)
            {
                game_over = true;
            }
        }

        if (game.has_update())
        {
            screen_manager.draw(game.board);
            screen_manager.draw(game.tetromino);
            screen_manager.show();
            
            lastUpdateTime = Clock::now();
            game.unset_update();

            repaints++;

            auto gametime = std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - game_start).count();
            std::cout << "Average repaints: " << repaints / (double)(gametime / 1000.0) << " per second" << '\n';
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