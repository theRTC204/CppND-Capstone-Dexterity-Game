#include "game.h"

Game::Game(const std::size_t gridWidth, const std::size_t gridHeight) :
    player(gridWidth, gridHeight),
    _gridWidth(gridWidth),
    _gridHeight(gridHeight)
{
    CreateGameBoard();
}

void Game::Run(Controller const &controller, Renderer &renderer, std::size_t targetFrameDuration)
{
    Uint32 titleTimestamp = SDL_GetTicks();
    Uint32 frameStart;
    Uint32 frameEnd;
    Uint32 frameDuration;
    int frameCount = 0;
    bool running = true;

    while (running)
    {
        frameStart = SDL_GetTicks();

        // Input, Update, Render - the main game loop.
        controller.HandleInput(running, player);
        Update();
        renderer.Render(player, this);

        frameEnd = SDL_GetTicks();

        // Keep track of how long each loop through the input/update/render cycle
        // takes.
        frameCount++;
        frameDuration = frameEnd - frameStart;

        // After every second, update the window title.
        if (frameEnd - titleTimestamp >= 1000)
        {
            renderer.UpdateWindowTitle(frameCount);
            frameCount = 0;
            titleTimestamp = frameEnd;
        }

        // If the time for this frame is too small (i.e. frameDuration is
        // smaller than the target kMsPerFrame), delay the loop to
        // achieve the correct frame rate.
        if (frameDuration < targetFrameDuration)
        {
            SDL_Delay(targetFrameDuration - frameDuration);
        }
    }
}

void Game::FlipTile(int tile_x, int tile_y)
{
    if (tile_x == 0 || tile_x == _gridWidth || tile_y == 0 || tile_y == _gridHeight)
    {
        // Prevent flipping tiles outside gameplay area
        return;
    }

    // TODO: Need to mutex the gameBoard
    gameBoard[tile_x][tile_y] = gameBoard[tile_x][tile_y] == 0 ? 1 : 0;
}

void Game::CreateGameBoard()
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

            // TODO: Figure out a randomizer for blocking a few spaces!
        }
        // TODO: Need to mutex the gameBoard
        gameBoard.push_back(column);
    }
}

void Game::Update()
{
    if (!player.alive) return;

    player.Update();

    // Stretch Goal: Implement some sort of enemy AI
}
