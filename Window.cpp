#include "Window.h"

static void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void GLAPIENTRY
MessageCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);
}

void Window::init() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

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
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		exit(EXIT_FAILURE);
	}

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);
}

void Window::update() {
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Window::end() {
	std::cout << "End of the road for you, window!" << std::endl;
}

int Window::getScreenWidth() const { return screenWidth; }

int Window::getScreenHeight() const { return screenHeight; }

std::string Window::getWindowName() const { return windowName; }

GLFWwindow* Window::getWindow() const { return window; }

void Window::setScreenWidth(int width) { screenWidth = width; }

void Window::setScreenHeight(int height) { screenHeight = height; }

void Window::setWindowName(const std::string& name) { windowName = name; }

void Window::setWindow(GLFWwindow* win) { window = win; }
