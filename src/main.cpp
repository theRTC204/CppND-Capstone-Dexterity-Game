#include <stdio.h>
#include "game.h"
#include "renderer.h"

int main(int argc, char *argv[])
{
	constexpr std::size_t kFramesPerSecond{60};
	constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
	constexpr std::size_t kScreenWidth{640};
	constexpr std::size_t kScreenHeight{480};
	constexpr std::size_t kGridWidth{32};
	constexpr std::size_t kGridHeight{32};

	Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
	// TODO: Instantiate the Controller
	Game game(kGridWidth, kGridHeight);
	game.Run(renderer, kMsPerFrame);

	printf("Game has terminated successfully!\n");

	return 0;
}
