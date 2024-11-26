#pragma once
#include "Renderer.h"
#include "Window.h"

class Game {

private:
	Window window;
	Renderer renderer;

public:
	Game() = default;
	~Game() = default;

	void init();
	void run();
	void end();

	Window getWindow() const { return window; }
	Renderer getRenderer() const { return renderer; }


};
