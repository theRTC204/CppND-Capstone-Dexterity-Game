#include <SDL.h>
#include <stdio.h>
#include "controller.h"
#include "player.h"

void Controller::ChangeDirection(Player &player, Player::Direction input) const
{
    player.direction = input;
}

void Controller::Activate(Player &player, Game &game) const
{
    game.FlipTile(player.activeTile.x, player.activeTile.y);
}

void Controller::HandleInput(bool &running, Player &player, Game &game) const
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT) {
            running = false;
        }
        else if (e.type == SDL_KEYDOWN)
        {
            switch (e.key.keysym.sym)
            {
                case SDLK_w:
                case SDLK_UP:
                    ChangeDirection(player, Player::Direction::kUp);
                    break;
                case SDLK_s:
                case SDLK_DOWN:
                    ChangeDirection(player, Player::Direction::kDown);
                    break;
                case SDLK_a:
                case SDLK_LEFT:
                    ChangeDirection(player, Player::Direction::kLeft);
                    break;
                case SDLK_d:
                case SDLK_RIGHT:
                    ChangeDirection(player, Player::Direction::kRight);
                    break;
                case SDLK_e:
                case SDLK_SPACE:
                    Activate(player, game);
                    break;
            }
        }
        else if (e.type == SDL_KEYUP)
        {
            ChangeDirection(player, Player::Direction::kNull);
        }
    }
}
