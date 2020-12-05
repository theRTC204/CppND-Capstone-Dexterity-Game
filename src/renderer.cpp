#include <stdio.h>
#include <string>
#include "renderer.h"

Renderer::Renderer(
    const std::size_t screenWidth,
    const std::size_t screenHeight,
    const std::size_t gridWidth,
    const std::size_t gridHeight)
: _screenWidth(screenWidth),
  _screenHeight(screenHeight),
  _gridWidth(gridWidth),
  _gridHeight(gridHeight)
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }

    // Create Window
    window = SDL_CreateWindow(
        "Dexterity Game",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        _screenWidth,
        _screenHeight,
        SDL_WINDOW_SHOWN);
    
    if (nullptr == window);
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (nullptr == renderer)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
    }
}

Renderer::~Renderer()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Renderer::Render()
{
    // The surface contained by the window
	SDL_Surface* screenSurface = NULL;

    // Get window surface
    screenSurface = SDL_GetWindowSurface(window);

    // Fill the surface white
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

    // Update the surface
    SDL_UpdateWindowSurface(window);
}

void Renderer::UpdateWindowTitle(int fps)
{
    std::string title = "Dexterity Game (FPS: " + std::to_string(fps) + ")";
    SDL_SetWindowTitle(window, title.c_str());
}
