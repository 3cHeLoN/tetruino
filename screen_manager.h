#pragma once

#define TILE_SIZE 40

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "board.h"


class ScreenManager
{
    private:
        SDL_Window* window;
    public:
        ScreenManager(int width, int height);
        void draw(Board *board);
        void show();
};