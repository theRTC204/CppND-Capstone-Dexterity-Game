#include <stdio.h>
#include "controller.h"
#include "game.h"
#include "renderer.h"

int main(int argc, char *argv[])
{
	constexpr std::size_t kFramesPerSecond{60};
	constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
	constexpr std::size_t kScreenWidth{800};
	constexpr std::size_t kScreenHeight{720};
	constexpr std::size_t kGridWidth{10};
	constexpr std::size_t kGridHeight{9};

	Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
	Controller controller;
	Game game(kGridWidth, kGridHeight);
	game.Run(controller, renderer, kMsPerFrame);

	printf("Game has terminated successfully!\n");

	return 0;
}
