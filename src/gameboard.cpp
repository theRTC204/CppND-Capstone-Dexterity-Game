#include "gameboard.h"

GameBoard::GameBoard(int gridWidth, int gridHeight) :
    _gridWidth(gridWidth),
    _gridHeight(gridHeight)
{
    Generate();
}

void GameBoard::Generate()
{
    for (int w = 0; w <= _gridWidth; w++)
    {
        std::vector<int> column{};
        for (int h = 0; h <= _gridHeight; h++)
        {
            if (w == 0 || h == 0 || w == _gridWidth || h == _gridHeight)
            {
                // The outer edges are not playable!
                column.push_back(-1);
            }
            else
            {
                // Initialize all grid coordinates as open!
                column.push_back(0);
            }
        }
        // TODO: Need to mutex the gameBoard
        _board.push_back(column);
    }

    // Randomizer for blocking a few spaces!
    int blockedCount = 0;
    do
    {
        SDL_Point blockedTile = SelectRandomTile();
        if (blockedTile.x == _gridWidth / 2 && blockedTile.y == _gridHeight / 2)
        {
            // Ensure the Player start location is never a blocked tile
            continue;
        }
        _board[blockedTile.x][blockedTile.y] = -1;
        blockedCount++;
    } while (blockedCount < 2);
}

int GameBoard::GetTileState(SDL_Point &coords)
{
    return _board[coords.x][coords.y];
}

void GameBoard::SetTileState(SDL_Point &coords, int state)
{
    _board[coords.x][coords.y] = state;
}

SDL_Point GameBoard::SelectRandomTile()
{
    return SDL_Point{
        RandomIntFromRange(1, _gridWidth - 1),
        RandomIntFromRange(1, _gridHeight - 1)
    };
}

std::vector<std::vector<int>> GameBoard::GetBoard()
{
    return _board;
}

int GameBoard::RandomIntFromRange(int low, int high)
{
    // Generate a random number using system clock as a seed
    // This ensure that successive runs generate truly random values
    // This method was adapted from: http://www.cplusplus.com/reference/random/uniform_int_distribution/operator()
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine gen(seed);
    std::uniform_int_distribution<int> distrib(1, 6);

    std::this_thread::sleep_for(std::chrono::milliseconds(1)); // Ensure next run generates another number

    return distrib(gen);
}
