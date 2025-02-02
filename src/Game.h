#pragma once
#include "Renderer.h"
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
