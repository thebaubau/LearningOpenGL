#pragma once
#include "Window.h"

class Game {

private:
	Window window;

public:
	Game() = default;
	~Game() = default;

	void Run();
	void End();

	Window getWindow() const { return window; }
};
