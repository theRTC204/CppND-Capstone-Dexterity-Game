#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "player.h"
#include "game.h"

class Game;

class Controller
{
public:
    void HandleInput(bool &running, Player &player, std::shared_ptr<Game> game) const;

private:
    void ChangeDirection(Player &player, Player::Direction input) const;
    void Activate(Player &player, std::shared_ptr<Game> game) const;
};

#endif
