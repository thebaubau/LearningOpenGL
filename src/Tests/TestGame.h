#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include "Test.h"

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

		

		//unsigned int Width, Height;
	private:
		void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

		glm::mat4 m_Projection;
		GLFWwindow* m_Window;
		std::unique_ptr<Shader> m_SpriteShader;
	};
}

