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

    window_width = width * TILE_SIZE;
    window_height = height * TILE_SIZE;

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
    SDL_Rect rect =  {col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE};
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
    // Create renderer
    if (renderer == NULL) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
    }

    // Clear the renderer
    SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);

    // Draw the colored square
    drawSquare(row, col, color, true);

    // Draw the border
    drawSquare(row, col, Color(146, 131, 116), false);
}

void ScreenManager::draw(Board &board)
{
    SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
    SDL_RenderClear(renderer);

    for (int row_index = 0; row_index < board.height; row_index++)
    {
        for (int col_index = 0; col_index < board.width; col_index++)
        {
            if (board.get_block(row_index, col_index) != 0)
            {
                drawBox(row_index, col_index, colormap.at((TetrominoType)(board.get_block(row_index, col_index))));
            }
        }
    }
}

void ScreenManager::draw(Tetromino &tetromino)
{
    int start_row = tetromino.get_row();
    int start_col = tetromino.get_col();
    for (int row = start_row; row < start_row + tetromino.height(); row++)
    {
        for (int col = start_col; col < start_col + tetromino.width(); col++)
        {
            if (row >= m_rows || col >= m_cols || col < 0 || row < 0)
            {
                continue;
            }
            if (tetromino(row - start_row, col - start_col) > 0)
            {
                drawBox(row, col, tetromino.get_color());
            }
        }
    }
}

void ScreenManager::show()
{
    // Present the renderer
    SDL_RenderPresent(renderer);
    SDL_UpdateWindowSurface(window);
}