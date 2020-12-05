#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <vector>
#include "controller.h"
#include "renderer.h"
#include "player.h"

class Renderer;

class Game
{
public:
    Game(const std::size_t gridWidth, const std::size_t gridHeight);

    void Run(Controller const &controller, Renderer &renderer, std::size_t targetFrameDuration);
    void FlipTile(int tile_x, int tile_y);
    
    // TODO: Encapsulate this inside a Class with RAII
    std::vector<std::vector<int>> gameBoard;

private:
    Player player;

    const std::size_t _gridWidth;
    const std::size_t _gridHeight;

    void CreateGameBoard();
    void Update();
};

#endif
