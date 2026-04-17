#include "TestGame.h"

namespace Test {
	TestGame::TestGame(GLFWwindow* window)
		: m_Window{ window }, state(GAME_ACTIVE), Keys()
	{
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);

		glDisable(GL_DEPTH_TEST);
		glfwSetWindowUserPointer(m_Window, this);
		glfwSetKeyCallback(m_Window, []
			(GLFWwindow* win, int key, int scancode, int action, int mods) {
				auto* self = static_cast<TestGame*>(glfwGetWindowUserPointer(win));
				self->KeyCallback(win, key, scancode, action, mods);
			});

		m_SpriteShader = std::make_unique<Shader>("res\\Shaders\\SpriteVertexShader.glsl", "res\\Shaders\\SpriteFragShader.glsl");

		m_SpriteShader->Bind();
		m_SpriteShader->SetMat4("projection", glm::ortho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f));

		m_SpriteRenderer = std::make_unique<SpriteRenderer>(*m_SpriteShader);

		std::shared_ptr<Texture> spriteTex = std::make_shared<Texture>("res\\Textures\\awesomeface.png", "diffuse");
		m_Brick = std::make_unique<GameObject>(glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), spriteTex);
	}

	TestGame::~TestGame() 
	{
		glEnable(GL_DEPTH_TEST);
		glfwSetKeyCallback(m_Window, nullptr);
	}

	void TestGame::OnCreate()
	{
	}

	void TestGame::ProcessInput(float deltaTime)
	{
	}

	void TestGame::OnUpdate(float deltaTime)
	{
	}

	void TestGame::OnRender(Renderer& renderer)
	{
		m_SpriteShader->Bind();
		m_SpriteRenderer->DrawSprite(*m_Brick->sprite, m_Brick->position, m_Brick->size, m_Brick->rotation, m_Brick->color);
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
