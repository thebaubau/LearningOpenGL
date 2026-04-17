#pragma once

#include "SpriteRenderer.h"
#include "Test.h"
#include "Texture.h"
#include "GameObject.h"

namespace Test {
	enum GameState {
		GAME_ACTIVE,
		GAME_MENU,
		GAME_WIN
	};

	class TestGame : public Test {
	public:
		TestGame(GLFWwindow* window);
		~TestGame();

		void OnCreate() override;
		void ProcessInput(float deltaTime) override;
		void OnUpdate(float deltaTime) override;
		void OnRender(Renderer& renderer) override;
		void OnImGuiRender() override;

		GameState state;
		bool Keys[1024];

		std::unique_ptr<SpriteRenderer> m_SpriteRenderer;
		std::unique_ptr<Shader> m_SpriteShader;
		std::unique_ptr<GameObject> m_Brick;

		//unsigned int Width, Height;
	private:
		void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

		GLFWwindow* m_Window;
	};
}

