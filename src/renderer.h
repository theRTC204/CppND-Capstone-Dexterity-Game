#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include <vector>
#include <memory>
#include "game.h"
#include "player.h"

class Game;

class Renderer
{
public:
    Renderer(
        const std::size_t screenWidth,
        const std::size_t screenHeight,
        const std::size_t gridWidth,
        const std::size_t gridHeight
    );
    ~Renderer();

    void Render(Player const player, Game const &game);
    void UpdateWindowTitle(int fps);

private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    const std::size_t _screenWidth;
    const std::size_t _screenHeight;
    const std::size_t _gridWidth;
    const std::size_t _gridHeight;
};

#endif
