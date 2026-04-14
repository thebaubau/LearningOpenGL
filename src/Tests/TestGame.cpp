#include "TestGame.h"

namespace Test {
	TestGame::TestGame(GLFWwindow* window)
		: m_Window{ window }, state(GAME_ACTIVE), Keys()
	{
		glDisable(GL_DEPTH_TEST);
		glfwSetWindowUserPointer(m_Window, this);
		glfwSetKeyCallback(m_Window, [](GLFWwindow* win, int key, int scancode, int action, int mods) {
			auto* self = static_cast<TestGame*>(glfwGetWindowUserPointer(win));
			self->KeyCallback(win, key, scancode, action, mods);
			});

	}

	TestGame::~TestGame()
	{
	}

	void TestGame::OnCreate()
	{
		m_Projection = glm::ortho(0.0f, 1280.0f, 820.0f, 0.0f, -1.0f, 1.0f);
		m_SpriteShader = std::make_unique<Shader>("res\\Shaders\\SpriteVertexShader.glsl", "res\\Shaders\\SpriteFragShader.glsl");


	}

	void TestGame::ProcessInput(float deltaTime)
	{
	}

	void TestGame::OnUpdate(float deltaTime)
	{
	}

	void TestGame::OnRender(Renderer& renderer)
	{

	}

	void TestGame::OnImGuiRender()
	{
	}

	void TestGame::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			std::cout << "Closing" << std::endl;
			glfwSetWindowShouldClose(window, true);
		}
		if (key >= 0 && key < 1024)
		{
			if (action == GLFW_PRESS)
				Keys[key] = true;
			else if (action == GLFW_RELEASE)
				Keys[key] = false;
		}
	}
}
