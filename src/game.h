#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include "controller.h"
#include "renderer.h"
#include "player.h"

class Controller;
class Renderer;

class Game
{
public:
    Game(const std::size_t gridWidth, const std::size_t gridHeight);

    void Run(Controller const &controller, Renderer &renderer, std::size_t targetFrameDuration);
    void FlipSingleTile(SDL_Point &&coords);
    void FlipChainedTiles(SDL_Point &&coords);
    
    // TODO: Encapsulate this inside a Class with RAII
    std::vector<std::vector<int>> gameBoard;

private:
    Player player;

    const std::size_t _gridWidth;
    const std::size_t _gridHeight;

    std::vector<SDL_Point> FindBoundingTiles(SDL_Point const &root);
    SDL_Point SelectRandomTile();
    int RandomIntFromRange(int low, int high);
    void CreateGameBoard();
    void Update();
};

#endif
