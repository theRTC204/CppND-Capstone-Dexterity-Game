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

void Renderer::Render(Player const player, Game const &game)
{
    SDL_Rect block;
    block.w = _screenWidth / _gridWidth;
    block.h = _screenHeight / _gridHeight;

    // Clear screen
    SDL_SetRenderDrawColor(renderer, 0x1E, 0x1E, 0x1E, 0xFF);
    SDL_RenderClear(renderer);

    // Render game board
    // TODO: Need to mutex the gameBoard
    const std::vector<std::vector<int>> board = game.gameBoard->GetBoard();
    for (int r = 1; r < board.size() - 2; r++)
    {
        for (int c = 1; c < board[r].size() - 2; c++)
        {
            if (game.playerWins)
            {
                SDL_SetRenderDrawColor(renderer, 0x84, 0xCE, 0x00, 0xFF);
            }
            else if (board[r][c] == 0)
            {
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            }
            else if (board[r][c] == -1)
            {
                SDL_SetRenderDrawColor(renderer, 0x1E, 0x1E, 0x1E, 0xFF);
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 0x00, 0x5B, 0x98, 0xFF);
            }
            
            block.x = r * block.w;
            block.y = c * block.h;
            SDL_RenderFillRect(renderer, &block);
        }
    }

    // Render the Player
    block.x = static_cast<int>(player.posX) * block.w;
    block.y = static_cast<int>(player.posY) * block.h;
    if (player.alive)
    {
        SDL_SetRenderDrawColor(renderer, 0x00, 0x7A, 0xCC, 0xFF);
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    }
    SDL_RenderFillRect(renderer, &block);

    // Update Screen
    SDL_RenderPresent(renderer);
}

void Renderer::UpdateWindowTitle(int fps)
{
    std::string title = "Dexterity Game (FPS: " + std::to_string(fps) + ")";
    SDL_SetWindowTitle(window, title.c_str());
}
