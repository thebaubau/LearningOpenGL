#include "Window.h"

static void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void Window::init() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	setWindow(glfwCreateWindow(screenWidth, screenHeight, windowName.c_str(), NULL, NULL));

	if (window == NULL) {
		std::cerr << "Failed to load GLFW window" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	// Able to resize window
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	// Mouse input
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		exit(EXIT_FAILURE);
	}

	glEnable(GL_DEPTH_TEST);
}

int Window::getScreenWidth() const { return screenWidth; }

int Window::getScreenHeight() const { return screenHeight; }

std::string Window::getWindowName() const { return windowName; }

GLFWwindow* Window::getWindow() const { return window; }

void Window::setScreenWidth(int width) { screenWidth = width; }

void Window::setScreenHeight(int height) { screenHeight = height; }

void Window::setWindowName(const std::string& name) { windowName = name; }

void Window::setWindow(GLFWwindow* win) { window = win; }
