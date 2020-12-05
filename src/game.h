#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <vector>
#include "renderer.h"

class Game
{
public:
    Game(const std::size_t gridWidth, const std::size_t gridHeight);

    void Run(Renderer &renderer, std::size_t targetFrameDuration);
    void FlipTile(int tile_x, int tile_y);
    
private:
    std::vector<std::vector<int>> _gameBoard;
    const std::size_t _gridWidth;
    const std::size_t _gridHeight;

    void CreateGameBoard();
    void Update();
};

#endif
