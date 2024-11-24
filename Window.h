#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>

class Window {

private:
	int screenWidth{ 800 };
	int screenHeight{ 600 };
	std::string windowName{ "Game" };

	GLFWwindow* window{};

public:
	Window() = default;
	~Window() = default;

	int getScreenWidth() const;
	int getScreenHeight() const;
	std::string getWindowName() const;
	GLFWwindow* getWindow() const;

	void setScreenWidth(int width);
	void setScreenHeight(int height);
	void setWindowName(const std::string& name);
	void setWindow(GLFWwindow* win);

	void init();
};

