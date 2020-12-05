#include "player.h"

void Player::Update()
{
    // Capture the Player position before update
    SDL_Point prevCell
    {
        static_cast<int>(posX),
        static_cast<int>(posY)
    };
    UpdatePosition();
    // Capture the Player position after update
    SDL_Point currentCell
    {
        static_cast<int>(posX),
        static_cast<int>(posY)
    };
}

void Player::UpdatePosition()
{
    // TODO: Only move Player while movement key is currently pressed
    switch (direction)
    {
        case Direction::kUp:
            posY -= speed;
            break;
        case Direction::kDown:
            posY += speed;
            break;
        case Direction::kLeft:
            posX -= speed;
            break;
        case Direction::kRight:
            posX += speed;
            break;
    }
}
