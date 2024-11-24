#include "Game.h"
#include "Window.h"
#include <iostream>

int main() {
	Game game;

	game.init();
	game.run();
	game.end();

	glfwTerminate();
	return 0;
}

