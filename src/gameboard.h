#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <SDL.h>
#include <chrono>
#include <random>
#include <thread>
#include <vector>

class GameBoard
{
public:
    GameBoard(int gridWidth, int gridHeight);

    int GetTileState(SDL_Point &coords);
    void SetTileState(SDL_Point &coords, int state);

    void Generate();
    std::vector<std::vector<int>> GetBoard();

private:
    SDL_Point SelectRandomTile();
    int RandomIntFromRange(int low, int high);

    std::vector<std::vector<int>> _board;
    int _gridWidth;
    int _gridHeight;
};

#endif
