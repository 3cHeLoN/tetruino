#pragma once

#define TILE_SIZE 40
#define BORDER_SIZE 2

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "color.h"
#include "board.h"


class ScreenManager
{
    private:
        int window_width, window_height;
        SDL_Window* window;
        SDL_Renderer* renderer;
        void drawBox(int row, int col, Color color);
        void drawSquare(int row, int col, Color color, bool fill);
    public:
        int m_rows, m_cols;
        ScreenManager(int width, int height);
        void draw(Board *board);
        void draw(Tetromino &tetromino);
        void show();
};