#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <map>
#include <chrono>
#ifdef _WIN32
#include <Windows.h>
#endif

#include "board.h"
#include "game.h"
#include "screen_manager.h"
#include "tetromino_factory.h"
#include "tetromino.h"

#define REPEAT_MS 50
#define INITIAL_REPEAT_MS  150

typedef std::chrono::high_resolution_clock Clock;
auto lastUpdateTime = Clock::now();
auto lastKeyRepeat = Clock::now();

int repaints = 0;
bool game_over = false;
bool keypressed = false;
bool repeat = false;
bool firstpress = true;
int repeat_ms = INITIAL_REPEAT_MS;

std::map<SDL_Keycode, bool> key_pressed_map =
{
    {SDLK_DOWN, false},
    {SDLK_UP, false},
    {SDLK_LEFT, false},
    {SDLK_RIGHT, false},
    {SDLK_a, false},
    {SDLK_s, false},
    {SDLK_SPACE, false},
};


int number_of_pressed_keys()
{
    int num_keys = 0;
    for (auto &pair : key_pressed_map)
    {
        num_keys += pair.second;
    }
    return num_keys;
}

void unset_keys()
{
    for (auto &pair : key_pressed_map)
    {
        pair.second = false;
    }
}

void handle_input(Game &game)
{
    SDL_Event e;
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
                // std::cout << "Key pressed" << '\n';
                keypressed = true;
                key_pressed_map[e.key.keysym.sym] = true;
                break;
            case SDL_KEYUP:
                // std::cout << "Key released" << '\n';
                key_pressed_map[e.key.keysym.sym] = false;

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
        if (key_pressed_map[SDLK_UP] | key_pressed_map[SDLK_s])
        {
            game.rotate(ClockWise);
            key_pressed_map[SDLK_UP] = false;
            key_pressed_map[SDLK_s] = false;
        }
        if (key_pressed_map[SDLK_a])
        {
            game.rotate(CounterClockWise);
            key_pressed_map[SDLK_a] = false;
        }
        if (key_pressed_map[SDLK_SPACE])
        {
            game.harddrop();
            key_pressed_map[SDLK_SPACE] = false;
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
            if (key_pressed_map[SDLK_LEFT])
            {
                game.move(DirectionLeft);
            }
            if (key_pressed_map[SDLK_RIGHT])
            {
                game.move(DirectionRight);
            }
            if (key_pressed_map[SDLK_DOWN])
            {
                game.move(DirectionDown);
            }
            firstpress = false;
        }
    }
}

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#elif __linux__
int main(int argc, char **argv)
#endif
{
    auto screen_manager = ScreenManager(10, 20);
    auto game = Game();
    std::cout << "TETRIS!" << '\n';

    while(!game_over)
    {
        handle_input(game);

        // Screen update.
        auto time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - lastUpdateTime);
        if (time_elapsed.count() >= 16)
        {
            // TODO: Should this be updated more frequently?
            auto success = game.update();
            if (!success)
            {
                game.game_over();
            }
        }

        if (game.has_update())
        {
            game.draw(screen_manager);
            screen_manager.show();
            
            lastUpdateTime = Clock::now();
            game.unset_update();
        }

        SDL_Delay(1);
    }

    std::cout << "GAME OVER!!!" << '\n';
    return 0;
}
