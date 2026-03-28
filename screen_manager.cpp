#include <algorithm>
#include <iostream>
#include <tuple>
#include "screen_manager.h"
#include "board.h"

// The music that will be played
Mix_Music *gMusic = NULL;

std::tuple<float, float, float> rgb_to_hsl(const Color &rgb)
{
    float r = rgb.getRed() / 255.0f;
    float g = rgb.getGreen() / 255.0f;
    float b = rgb.getBlue() / 255.0f;

    float max_val = std::max({r, g, b});
    float min_val = std::min({r, g, b});
    float h, s, l;

    // Hue calculation
    if (max_val == min_val)
    {
        h = 0;
    }
    else if (max_val == r)
    {
        h = 60 * (g - b) / (max_val - min_val);
    }
    else if (max_val == g)
    {
        h = 60 * (2 + (b - r) / (max_val - min_val));
    }
    else
    {
        h = 60 * (4 + (r - g) / (max_val - min_val));
    }
    if (h < 0)
        h += 360;

    // Lightness calculation
    l = (max_val + min_val) / 2;

    // Saturation calculation
    if (max_val == min_val)
    {
        s = 0;
    }
    else if (l <= 0.5)
    {
        s = (max_val - min_val) / (2 * l);
    }
    else
    {
        s = (max_val - min_val) / (2 - 2 * l);
    }

    return std::make_tuple(h, s, l);
}

Color hsl_to_rgb(const std::tuple<float, float, float> &hsl)
{
    float h = std::get<0>(hsl);
    float s = std::get<1>(hsl);
    float l = std::get<2>(hsl);

    float c = (1 - std::abs(2 * l - 1)) * s;
    float x = c * (1 - std::abs(fmod(h / 60, 2) - 1));
    float m = l - c / 2;
    float r, g, b;

    if (h >= 0 && h < 60)
    {
        r = c;
        g = x;
        b = 0;
    }
    else if (h >= 60 && h < 120)
    {
        r = x;
        g = c;
        b = 0;
    }
    else if (h >= 120 && h < 180)
    {
        r = 0;
        g = c;
        b = x;
    }
    else if (h >= 180 && h < 240)
    {
        r = 0;
        g = x;
        b = c;
    }
    else if (h >= 240 && h < 300)
    {
        r = x;
        g = 0;
        b = c;
    }
    else
    {
        r = c;
        g = 0;
        b = x;
    }

    return Color(static_cast<int>((r + m) * 255),
                 static_cast<int>((g + m) * 255),
                 static_cast<int>((b + m) * 255));
}

Color adjust_lightness(const Color &rgb, float factor)
{
    auto hsl = rgb_to_hsl(rgb);
    float new_l = std::get<2>(hsl) * factor; // std::max(0.0f, std::min(1.0f, std::get<2>(hsl) - factor));
    std::get<2>(hsl) = new_l;
    return hsl_to_rgb(hsl);
}

ScreenManager::ScreenManager(int width, int height)
{
    m_rows = height;
    m_cols = width;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        std::cerr << "Could not setup the screen." << '\n';
    }

    // Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }

    // Load music
    gMusic = Mix_LoadMUS("assets//type_a.mp3");
    if (gMusic == NULL)
    {
        printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
    }

    // Play the music
    Mix_PlayMusic(gMusic, -1);

    window_width = width * m_tile_size;
    window_height = height * m_tile_size;

    // Create window
    window = SDL_CreateWindow("TETRIS!", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, window_width, window_height, 0);
    if (!window)
    {
        std::cout << "Could not create window" << '\n';
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
    }
}

/*!
    Draws a triangle based on the anchor point (row, col) (upper-left point).

    @param row The row of the anchor point.
    @param col The column of the anchor point.
    @param upper Whether to fill the bottom or upper part of the square
*/
void ScreenManager::drawTriangle(int row, int col, Color color, bool upper, double factor)
{
    SDL_Vertex vertices[3];
    int border_size = (int)(0.2 * m_tile_size);

    auto darkened_color = adjust_lightness(color, factor);

    if (upper)
    {
        vertices[0].position.x = col * m_tile_size + border_size;
        vertices[0].position.y = row * m_tile_size + border_size;
        vertices[1].position.x = col * m_tile_size + m_tile_size - border_size;
        vertices[1].position.y = row * m_tile_size + border_size;
        vertices[2].position.x = col * m_tile_size + border_size;
        vertices[2].position.y = row * m_tile_size + m_tile_size - border_size;
    }
    else
    {
        vertices[0].position.x = col * m_tile_size + m_tile_size - border_size;
        vertices[0].position.y = row * m_tile_size + m_tile_size - border_size;
        vertices[1].position.x = col * m_tile_size + border_size;
        vertices[1].position.y = row * m_tile_size + m_tile_size - border_size;
        vertices[2].position.x = col * m_tile_size + m_tile_size - border_size;
        vertices[2].position.y = row * m_tile_size + border_size;
    }

    for (auto i = 0; i < 3; i++)
    {
        vertices[i].color.r = darkened_color.getRed();
        vertices[i].color.g = darkened_color.getGreen();
        vertices[i].color.b = darkened_color.getBlue();
        vertices[i].color.a = 255;
    }

    SDL_SetRenderDrawColor(renderer, darkened_color.getRed(), darkened_color.getGreen(), darkened_color.getBlue(), 255);
    SDL_RenderGeometry(renderer, NULL, vertices, 3, NULL, 0);
}

void ScreenManager::drawSquare(int row, int col, const Color color, bool fill)
{
    SDL_Rect rect = {col * m_tile_size, row * m_tile_size, m_tile_size, m_tile_size};
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

void ScreenManager::drawBox(int row, int col, const Color color, bool filled)
{
    if (row > m_rows || col > m_cols)
    {
        return;
    }

    // Create renderer
    if (renderer == NULL)
    {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
    }

    // Draw the colored square
    drawSquare(row, col, color, true);

    auto darkened_color = adjust_lightness(color, 0.8);
    // Draw the border
    drawSquare(row, col, darkened_color, false);

    // Draw triangle
    if (filled)
    {
        drawTriangle(row, col, color, true, 0.8);
    }
    else
    {
        drawTriangle(row, col, color, true, 1.2);
    }
    drawTriangle(row, col, color, false, 0.8);
}

void ScreenManager::clear_screen()
{
    SDL_RenderClear(renderer);
}

void ScreenManager::set_background(const Color &color)
{
    SDL_SetRenderDrawColor(renderer, color.getRed(), color.getGreen(), color.getBlue(), 255);
}

void ScreenManager::show()
{
    // Present the renderer
    SDL_RenderPresent(renderer);
    SDL_UpdateWindowSurface(window);
}
