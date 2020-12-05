#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>

class Player
{
public:
    enum class Direction { kNull, kUp, kDown, kLeft, kRight };

    // TODO: Determine how to constrain Player to gameBoard bounds
    Player(int gridWidth, int gridHeight) :
        _gridWidth(gridWidth),
        _gridHeight(gridHeight),
        posX(gridWidth / 2),
        posY(gridHeight / 2) {}

    void Update();

    Direction direction = Direction::kNull;

    float speed{0.1f};
    bool alive{true};
    float posX;
    float posY;
private:
    void UpdatePosition();

    int _gridWidth;
    int _gridHeight;
};

#endif
