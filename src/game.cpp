#include "game.h"

Game::Game(const std::size_t gridWidth, const std::size_t gridHeight) :
    player(gridWidth, gridHeight),
    gameBoard(std::make_shared<GameBoard>(gridWidth, gridHeight)),
    _gridWidth(gridWidth),
    _gridHeight(gridHeight),
    _self(this) { }

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
        controller.HandleInput(running, player, (*this));
        Update();
        renderer.Render(player, (*this));

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

void Game::FlipSingleTile(SDL_Point &&coords, int sleepMultiplier)
{
    if (gameBoard->GetTileState(coords) == -1)
    {
        // Prevent flipping tiles outside gameplay area
        // or tiles marked as blocked
        return;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(250 * sleepMultiplier));

    // TODO: Need to mutex the gameBoard
    int newState = gameBoard->GetTileState(coords) == 0 ? 1 : 0;
    gameBoard->SetTileState(coords, newState);
}

void Game::FlipChainedTiles(SDL_Point &&coords)
{
    int sleepMultiplier = 0;
    std::vector<std::thread> threads;
    
    SDL_Point current = SDL_Point(coords);
    threads.emplace_back(std::thread(&Game::FlipSingleTile, _self, std::move(current), sleepMultiplier));

    std::vector<SDL_Point> connections = FindBoundingTiles(coords);
    for (auto conn : connections)
    {
        // Reset the sleep multiplier for a new row/column
        sleepMultiplier = 0;
        for (int i = coords.x - 1; i > conn.x; i--)
        {
            SDL_Point tile{i, coords.y};
            threads.emplace_back(std::thread(&Game::FlipSingleTile, _self, std::move(tile), sleepMultiplier));
            sleepMultiplier++;
        }

        // Reset the sleep multiplier for a new row/column
        sleepMultiplier = 0;
        for (int i = coords.y - 1; i > conn.y; i--)
        {
            SDL_Point tile{coords.x, i};
            threads.emplace_back(std::thread(&Game::FlipSingleTile, _self, std::move(tile), sleepMultiplier));
            sleepMultiplier++;
        }

        // Reset the sleep multiplier for a new row/column
        sleepMultiplier = 0;
        for (int i = coords.x + 1; i < conn.x; i++)
        {
            SDL_Point tile{i, coords.y};
            threads.emplace_back(std::thread(&Game::FlipSingleTile, _self, std::move(tile), sleepMultiplier));
            sleepMultiplier++;
        }

        // Reset the sleep multiplier for a new row/column
        sleepMultiplier = 0;
        for (int i = coords.y + 1; i < conn.y; i++)
        {
            SDL_Point tile{coords.x, i};
            threads.emplace_back(std::thread(&Game::FlipSingleTile, _self, std::move(tile), sleepMultiplier));
            sleepMultiplier++;
        }
    }

    for (auto &thread : threads)
    {
        thread.detach();
    }
}

std::vector<SDL_Point> Game::FindBoundingTiles(SDL_Point const &root)
{
    std::vector<SDL_Point> connections;

    for (int i = root.x - 1; i >= 1; i--)
    {
        SDL_Point tile{i, root.y};
        int tileState = gameBoard->GetTileState(tile);

        if (tileState == -1)
            break; // Bail out if we hit a blocked tile!
        if (tileState == 1)
        {
            connections.push_back(tile);
            break;
        }
    }

    for (int i = root.y - 1; i >= 1; i--)
    {
        SDL_Point tile{root.x, i};
        int tileState = gameBoard->GetTileState(tile);

        if (tileState == -1)
            break; // Bail out if we hit a blocked tile!
        if (tileState == 1)
        {
            connections.push_back(tile);
            break;
        }
    }

    for (int i = root.x + 1; i <= _gridWidth - 1; i++)
    {
        SDL_Point tile{i, root.y};
        int tileState = gameBoard->GetTileState(tile);

        if (tileState == -1)
            break; // Bail out if we hit a blocked tile!
        if (tileState == 1)
        {
            connections.push_back(tile);
            break;
        }
    }

    for (int i = root.y + 1; i <= _gridHeight - 1; i++)
    {
        SDL_Point tile{root.x, i};
        int tileState = gameBoard->GetTileState(tile);

        if (tileState == -1)
            break; // Bail out if we hit a blocked tile!
        if (tileState == 1)
        {
            connections.push_back(tile);
            break;
        }
    }

    return connections;
}

bool Game::CheckWinCondition()
{
    for (int r = 1; r < _gridHeight - 2; r++)
    {
        for (int c = 1; c < _gridWidth - 2; c++)
        {
            SDL_Point tile{r, c};
            if (gameBoard->GetTileState(tile) == 0) {
                return false;
            }
        }
    }
    return true;
}

void Game::Update()
{
    if (!player.alive) return;

    playerWins = CheckWinCondition();
    if (playerWins)
    {
        return;
    }

    player.Update();

    // Stretch Goal: Implement some sort of enemy AI
}
