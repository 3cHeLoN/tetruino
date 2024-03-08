#include <algorithm>
#include "screen_manager.h"

ScreenManager::ScreenManager(int width, int height)
{
    m_rows = height;
    m_cols = width;

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Could not setup the screen." << '\n';
    }

    window_width = width * m_tile_size;
    window_height = height * m_tile_size;

    // Create window
    window = SDL_CreateWindow("TETRIS!", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, window_width, window_height, 0);
    if (!window)
    {
        std::cout <<  "Could not create window" << '\n';
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
    }
}

void ScreenManager::drawSquare(int row, int col, Color color, bool fill)
{
    SDL_Rect rect =  {col * m_tile_size, row * m_tile_size, m_tile_size, m_tile_size};
    SDL_SetRenderDrawColor(renderer, color.getRed(), color.getGreen(), color.getBlue(), 255);
    if (fill)
    {
        SDL_RenderFillRect(renderer, &rect);
    }
    else
    {
        SDL_RenderDrawRect(renderer, &rect);
    }
}

void ScreenManager::drawBox(int row, int col, Color color)
{
    if (row > m_rows || col > m_cols)
    {
        return;
    }

    // Create renderer
    if (renderer == NULL) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
    }

    // Draw the colored square
    drawSquare(row, col, color, true);

    // Draw the border
    drawSquare(row, col, Color(146, 131, 116), false);
}

void ScreenManager::clear_screen()
{
    SDL_RenderClear(renderer);
}

void ScreenManager::set_background(Color &color)
{
    SDL_SetRenderDrawColor(renderer,  color.getRed(), color.getGreen(), color.getBlue(), 255);
}

void ScreenManager::show()
{
    // Present the renderer
    SDL_RenderPresent(renderer);
    SDL_UpdateWindowSurface(window);
}