#include "Game.h"

float mixValue{ 1.2f };
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

float lastX = 800 / 2.0f;
float lastY = 600 / 2.0f;
bool firstMouse = true;

Camera m_Camera;

void processInput(GLFWwindow* w);

void mouseCallback(GLFWwindow* window, double xposIn, double yposIn);

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

void Game::init() {
	window.setScreenWidth(800);
	window.setScreenHeight(600);
	window.setWindowName("Lighting");

	window.init();
	renderer.init();

	m_Camera = renderer.getCamera();

	glfwSetCursorPosCallback(window.getWindow(), mouseCallback);
	glfwSetScrollCallback(window.getWindow(), scrollCallback);
}

void Game::run() {
	std::cout << "Game running" << std::endl;

	auto gameWindow = window.getWindow();

	/*renderer.getShader().use();
	renderer.getShader().setInt("texture1", 0);
	renderer.getShader().setInt("texture2", 1);*/

	while (!glfwWindowShouldClose(gameWindow))
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(gameWindow);

		window.update();
		renderer.update();
	}
}

void Game::end() {
	std::cout << "Game Ended" << std::endl;
	glfwTerminate();
}

void processInput(GLFWwindow* w) {
	if (glfwGetKey(w, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(w, true);

	if (glfwGetKey(w, GLFW_KEY_UP) == GLFW_PRESS)
	{
		mixValue += 0.001f;
		if (mixValue > 1.0f)
			mixValue = 1.0f;
	}

	if (glfwGetKey(w, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		mixValue -= 0.001f;
		if (mixValue < 0.0f)
			mixValue = 0.0f;
	}

	if (glfwGetKey(w, GLFW_KEY_W) == GLFW_PRESS) {
		m_Camera.ProcessKeyboard(FORWARD, deltaTime);
		std::cout << "W" << std::endl;
	}
	if (glfwGetKey(w, GLFW_KEY_S) == GLFW_PRESS) {

		std::cout << "S" << std::endl;
		m_Camera.ProcessKeyboard(BACKWARD, deltaTime);
	}
	if (glfwGetKey(w, GLFW_KEY_A) == GLFW_PRESS)
	{
		std::cout << "A" << std::endl;
		m_Camera.ProcessKeyboard(LEFT, deltaTime);

	}
	if (glfwGetKey(w, GLFW_KEY_D) == GLFW_PRESS)
		std::cout << "S" << std::endl;
	{

		m_Camera.ProcessKeyboard(RIGHT, deltaTime);
	}
};

void mouseCallback(GLFWwindow* window, double xposIn, double yposIn) {
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	m_Camera.ProcessMouseMovement(xoffset, yoffset);
};

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	m_Camera.ProcessMouseScroll(static_cast<float>(yoffset));
};

