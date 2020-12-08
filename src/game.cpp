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
        controller.HandleInput(running, player, (*this));
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

void Game::FlipSingleTile(SDL_Point &&coords)
{
    if (gameBoard[coords.x][coords.y] == -1)
    {
        // Prevent flipping tiles outside gameplay area
        // or tiles marked as blocked
        return;
    }

    // TODO: Need to mutex the gameBoard
    gameBoard[coords.x][coords.y] = gameBoard[coords.x][coords.y] == 0 ? 1 : 0;
}

void Game::FlipChainedTiles(SDL_Point &&coords)
{
    SDL_Point current = SDL_Point(coords);
    FlipSingleTile(std::move(current));

    std::vector<SDL_Point> connections = FindBoundingTiles(coords);
    for (auto conn : connections)
    {
        for (int i = coords.x - 1; i > conn.x; i--)
        {
            SDL_Point tile{i, coords.y};
            FlipSingleTile(std::move(tile));
        }
        for (int i = coords.y - 1; i > conn.y; i--)
        {
            SDL_Point tile{coords.x, i};
            FlipSingleTile(std::move(tile));
        }
        for (int i = coords.x + 1; i < conn.x; i++)
        {
            SDL_Point tile{i, coords.y};
            FlipSingleTile(std::move(tile));
        }
        for (int i = coords.y + 1; i < conn.y; i++)
        {
            SDL_Point tile{coords.x, i};
            FlipSingleTile(std::move(tile));
        }
    }
}

std::vector<SDL_Point> Game::FindBoundingTiles(SDL_Point const &root)
{
    std::vector<SDL_Point> connections;

    for (int i = root.x - 1; i >= 1; i--)
    {
        if (gameBoard[i][root.y] == 1)
        {
            connections.emplace_back(SDL_Point{i, root.y});
            break;
        }
    }

    for (int i = root.y - 1; i >= 1; i--)
    {
        if (gameBoard[root.x][i] == 1)
        {
            connections.emplace_back(SDL_Point{root.x, i});
            break;
        }
    }

    for (int i = root.x + 1; i <= _gridWidth - 1; i++)
    {
        if (gameBoard[i][root.y] == 1)
        {
            connections.emplace_back(SDL_Point{i, root.y});
            break;
        }
    }

    for (int i = root.y + 1; i <= _gridHeight - 1; i++)
    {
        if (gameBoard[root.x][i] == 1)
        {
            connections.emplace_back(SDL_Point{root.x, i});
            break;
        }
    }

    return connections;
}

SDL_Point Game::SelectRandomTile()
{
    return SDL_Point{
        RandomIntFromRange(1, _gridWidth - 1),
        RandomIntFromRange(1, _gridHeight - 1)
    };
}

int Game::RandomIntFromRange(int low, int high)
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
        }
        // TODO: Need to mutex the gameBoard
        gameBoard.push_back(column);
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
        gameBoard[blockedTile.x][blockedTile.y] = -1;
        blockedCount++;
    } while (blockedCount < 2);
}

void Game::Update()
{
    if (!player.alive) return;

    player.Update();

    // Stretch Goal: Implement some sort of enemy AI
}
