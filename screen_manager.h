#pragma once

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
        void drawSquare(int row, int col, Color color, bool fill);
        int m_tile_size = 35;
        int m_rows, m_cols;
    public:
        void drawBox(int row, int col, Color color);
        ScreenManager(int width, int height);
        void set_background(Color &color);
        void clear_screen();
        void show();
        int tile_size() { return m_tile_size; };
        int width() { return window_width; };
        int height() { return window_height; };
};