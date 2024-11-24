#pragma once
#include "Window.h"
#include <iostream>

class Game {

private:
	Window window;

public:
	Game() = default;

	void init();
	void run();
	void end();

	Window getWindow() const { return window; }
};
