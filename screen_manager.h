#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_mixer.h>

#include "color.h"

class ScreenManager
{
private:
    int window_width, window_height;
    SDL_Window *window;
    SDL_Renderer *renderer;
    void drawSquare(int row, int col, Color color, bool fill);
    void drawTriangle(int row, int col, Color color, bool upper, double factor = 1.0);
    int m_tile_size = 35;
    int m_rows, m_cols;

public:
    void drawBox(int row, int col, Color color, bool filled);
    ScreenManager(int width, int height);
    void set_background(const Color &color);
    void clear_screen();
    void show();
    int tile_size() { return m_tile_size; };
    int width() { return window_width; };
    int height() { return window_height; };
};