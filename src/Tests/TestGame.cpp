#include "TestGame.h"

namespace Test {
	const glm::vec2 PLAYER_SIZE{ 100.0f, 20.0f };
	const float PLAYER_VELOCITY{ 500.0f };
	const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
	const float BALL_RADIUS = 12.5f;

	TestGame::TestGame(GLFWwindow* window)
		: m_Window{ window }, state(GAME_ACTIVE), Keys()
	{
		glfwGetFramebufferSize(window, &m_Width, &m_Height);

		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glfwSetWindowUserPointer(m_Window, this);
		glfwSetKeyCallback(m_Window, []
			(GLFWwindow* win, int key, int scancode, int action, int mods) {
				auto* self = static_cast<TestGame*>(glfwGetWindowUserPointer(win));
				self->KeyCallback(win, key, scancode, action, mods);
			});


		m_SpriteShader = std::make_unique<Shader>("res\\Shaders\\SpriteVertexShader.glsl", "res\\Shaders\\SpriteFragShader.glsl");

		m_SpriteShader->Bind();
		m_SpriteShader->SetMat4("projection", glm::ortho(0.0f, (float)m_Width, (float)m_Height, 0.0f, -1.0f, 1.0f));

		m_SpriteRenderer = std::make_unique<SpriteRenderer>(*m_SpriteShader);
		m_Face = std::make_shared<Texture>("res\\Textures\\awesomeface.png", "diffuse");
		m_Background = std::make_shared<Texture>("res\\Textures\\breakout\\background.jpg", "diffuse");
		m_Paddle = std::make_shared<Texture>("res\\Textures\\breakout\\paddle.png", "diffuse");

		m_Player = std::make_unique<GameObject>(glm::vec2(this->m_Width / 2 - PLAYER_SIZE.x / 2, this->m_Height - PLAYER_SIZE.y - 20), PLAYER_SIZE, m_Paddle);

		glm::vec2 ballPos = m_Player->position + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS,
			-BALL_RADIUS * 2.0f);

		m_Ball = std::make_unique<BallObject>(ballPos, BALL_RADIUS, m_Face, glm::vec3(1.0f), INITIAL_BALL_VELOCITY);

		GameLevel one; one.Load("res\\Levels\\level01.txt", this->m_Width, this->m_Height / 2);
		GameLevel two; two.Load("res\\Levels\\level02.txt", this->m_Width, this->m_Height / 2);
		GameLevel three; three.Load("res\\Levels\\level03.txt", this->m_Width, this->m_Height / 2);
		GameLevel four; four.Load("res\\Levels\\level04.txt", this->m_Width, this->m_Height / 2);

		this->Levels.push_back(one);
		this->Levels.push_back(two);
		this->Levels.push_back(three);
		this->Levels.push_back(four);
		this->Level = 1;
	}

	TestGame::~TestGame() 
	{
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
		glfwSetKeyCallback(m_Window, nullptr);
	}

	void TestGame::OnCreate()
	{
	}

	void TestGame::ProcessInput(float deltaTime)
	{
		if (this->state == GAME_ACTIVE)
		{
			float velocity = PLAYER_VELOCITY * deltaTime;
			// move playerboard
			if (this->Keys[GLFW_KEY_A])
			{
				if (m_Player->position.x >= 0.0f)
				{
					m_Player->position.x -= velocity;
					if (m_Ball->stuck)
						m_Ball->position.x -= velocity;
				}
			}
			if (this->Keys[GLFW_KEY_D])
			{
				if (m_Player->position.x <= this->m_Width - m_Player->size.x)
				{
					m_Player->position.x += velocity;
					if (m_Ball->stuck)
						m_Ball->position.x += velocity;
				}
			}
			if (this->Keys[GLFW_KEY_SPACE])
				m_Ball->stuck = false;
		}
	}

	void TestGame::OnUpdate(float deltaTime)
	{
		m_Ball->Move(deltaTime, this->m_Width);
	}

	void TestGame::OnRender(Renderer& renderer)
	{
		m_SpriteShader->Bind();
		if (this->state == GAME_ACTIVE)
		{
			m_SpriteRenderer->DrawSprite(*m_Background, glm::vec2(0.0f, 0.0f), glm::vec2(this->m_Width, this->m_Height), 0.0f);
			m_Player->Draw(*m_SpriteRenderer);
			m_Ball->Draw(*m_SpriteRenderer);

			this->Levels[this->Level].Draw(*m_SpriteRenderer);
		}
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
