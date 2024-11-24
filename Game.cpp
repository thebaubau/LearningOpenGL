#include "Game.h"

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void Game::init() {
	int screenWidth{ 800 };
	int screenHeight{ 600 };
	std::string windowName{ "Lighting" };

	//Window window;
	window.setScreenWidth(screenWidth);
	window.setScreenHeight(screenHeight);
	window.setWindowName(windowName);

	window.init();
}

void Game::run() {
	std::cout << "Game running" << std::endl;

	auto gameWindow = window.getWindow();

	while (!glfwWindowShouldClose(gameWindow))
	{
		processInput(gameWindow);
		glfwSwapBuffers(gameWindow);
		glfwPollEvents();
	}
}

void Game::end() {
	std::cout << "Game Ended" << std::endl;
}
