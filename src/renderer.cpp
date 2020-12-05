#include <stdio.h>
#include <string>
#include "renderer.h"

Renderer::Renderer(
    const std::size_t screen_width,
    const std::size_t screen_height,
    const std::size_t grid_width,
    const std::size_t grid_height)
: screen_width(screen_width),
  screen_height(screen_height),
  grid_width(grid_width),
  grid_height(grid_height)
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }

    // Create Window
    sdl_window = SDL_CreateWindow(
        "Dexterity Game",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        screen_width,
        screen_height,
        SDL_WINDOW_SHOWN);
    
    if (nullptr == sdl_window);
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    }

    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
    if (nullptr == sdl_renderer)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
    }
}

Renderer::~Renderer()
{
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();
}

void Renderer::Render()
{
    // The surface contained by the window
	SDL_Surface* screenSurface = NULL;

    // Get window surface
    screenSurface = SDL_GetWindowSurface(sdl_window);

    // Fill the surface white
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

    // Update the surface
    SDL_UpdateWindowSurface(sdl_window);
}

void Renderer::UpdateWindowTitle(int fps)
{
    std::string title = "Dexterity Game (FPS: " + std::to_string(fps) + ")";
    SDL_SetWindowTitle(sdl_window, title.c_str());
}
