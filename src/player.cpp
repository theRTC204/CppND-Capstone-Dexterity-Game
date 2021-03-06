#include <memory>
#include "player.h"

Player::Player(int gridWidth, int gridHeight) :
    posX(gridWidth / 2),
    posY(gridHeight / 2),
    _gridWidth(gridWidth),
    _gridHeight(gridHeight)
{
    SDL_Point startingCell
    {
        static_cast<int>(posX),
        static_cast<int>(posY)
    };
    UpdateActiveTile(std::move(startingCell));
}

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

    // Update the active tile if the Player has moved to a new cell.
    if (currentCell.x != prevCell.x || currentCell.y != prevCell.y)
    {
        UpdateActiveTile(std::move(currentCell));
    }
}

void Player::SetDirection(Direction direction)
{
    _direction = direction;
}

void Player::UpdatePosition()
{
    switch (_direction)
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
        case Direction::kNull:
        default:
            break;
    }
}

void Player::UpdateActiveTile(SDL_Point &&tile)
{
    activeTile = std::move(tile);
}
