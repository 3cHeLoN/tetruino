#include "screen_manager.h"


ScreenManager::ScreenManager(int width, int height)
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Could not setup the screen." << '\n';
    }

    window = SDL_CreateWindow("TETRIS!", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, width * TILE_SIZE, height * TILE_SIZE, 0);
    
    if (!window)
    {
        std::cout <<  "Could not create window" << '\n';
    }
}

void ScreenManager::draw(Board *board)
{

}

void ScreenManager::show()
{
    SDL_UpdateWindowSurface(window);
}