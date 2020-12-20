#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>

class Player
{
public:
    enum class Direction { kNull, kUp, kDown, kLeft, kRight };

    // TODO: Determine how to constrain Player to gameBoard bounds
    Player(int gridWidth, int gridHeight);

    void Update();
    void SetDirection(Direction direction);

    float speed{0.1f};
    bool alive{true};
    float posX;
    float posY;
    SDL_Point activeTile;

private:
    void UpdatePosition();
    void UpdateActiveTile(SDL_Point &&tile);

    Direction _direction = Direction::kNull;

    int _gridWidth;
    int _gridHeight;
};

#endif
