#include "TestGame.h"
using namespace Collision;

namespace Test {
	const glm::vec2 PLAYER_SIZE{ 100.0f, 20.0f };
	const float PLAYER_VELOCITY{ 500.0f };
	const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
	const float BALL_RADIUS = 12.5f;
	const float QUAD_VERTICES[] = {
		-1, -1, 0, 0,
		 1, -1, 1, 0,
		 1,  1, 1, 1,
		-1, -1, 0, 0,
		 1,  1, 1, 1,
		-1,  1, 0, 1
	};

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

		float offset = 1.0f / 300.0f;

		glm::vec2 offsets[9] = {
			glm::vec2(-offset,  offset), // top-left
			glm::vec2(0.0f,    offset),  // top-center
			glm::vec2(offset,  offset),  // top-right
			glm::vec2(-offset,  0.0f),   // center-left
			glm::vec2(0.0f,    0.0f),    // center-center
			glm::vec2(offset,  0.0f),    // center-right
			glm::vec2(-offset, -offset), // bottom-left
			glm::vec2(0.0f,   -offset),  // bottom-center
			glm::vec2(offset, -offset)   // bottom-right    
		};

		int edge_kernel[9] = {
			-1, -1, -1,
			-1,  8, -1,
			-1, -1, -1
		};

		float blur_kernel[9] = {
			1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f,
			2.0f / 16.0f, 4.0f / 16.0f, 2.0f / 16.0f,
			1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f
		};

		// Shaders
		m_SpriteShader = std::make_unique<Shader>("res\\Shaders\\SpriteVertexShader.glsl", "res\\Shaders\\SpriteFragShader.glsl");
		m_ParticleShader = std::make_unique<Shader>("res\\Shaders\\ParticleVertexShader.glsl", "res\\Shaders\\ParticleFragmentShader.glsl");
		m_ScreenShader = std::make_unique<Shader>("res\\Shaders\\FrameBufferVertexShader.glsl", "res\\Shaders\\FrameBufferFragShader.glsl");

		m_ScreenShader->Bind();
		m_ScreenShader->SetVec2Array("offsets", 9, offsets);
		m_ScreenShader->SetIntArray("edge_kernel", 9, edge_kernel);
		m_ScreenShader->SetFloatArray("blur_kernel", 9, blur_kernel);
		m_ScreenShader->Unbind();

		// Sprite Renderer
		m_SpriteShader->Bind();
		m_SpriteShader->SetMat4("projection", glm::ortho(0.0f, (float)m_Width, (float)m_Height, 0.0f, -1.0f, 1.0f));
		m_SpriteRenderer = std::make_unique<SpriteRenderer>(*m_SpriteShader);

		// Textures
		m_Face = std::make_shared<Texture>("res\\Textures\\awesomeface.png", "diffuse");
		m_Background = std::make_shared<Texture>("res\\Textures\\breakout\\background.jpg", "diffuse");
		m_Paddle = std::make_shared<Texture>("res\\Textures\\breakout\\paddle.png", "diffuse");
		m_ParticleTexture = std::make_shared<Texture>("res\\Textures\\breakout\\particle.png", "diffuse");

		// GameObjects
		m_Player = std::make_unique<GameObject>(glm::vec2(this->m_Width / 2 - PLAYER_SIZE.x / 2, this->m_Height - PLAYER_SIZE.y - 20), PLAYER_SIZE, m_Paddle);

		glm::vec2 ballPos = m_Player->position + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS,
			-BALL_RADIUS * 2.0f);

		m_Ball = std::make_unique<BallObject>(ballPos, BALL_RADIUS, m_Face, glm::vec3(1.0f), INITIAL_BALL_VELOCITY);

		m_ParticleShader->Bind();
		m_ParticleShader->SetMat4("projection", glm::ortho(0.0f, (float)m_Width, (float)m_Height, 0.0f, -1.0f, 1.0f));

		m_Particles = std::make_unique<ParticleGenerator>(m_ParticleTexture, *m_ParticleShader, 500);

		// Framebuffer Postprocessing
		m_ScreenBuffer = std::make_unique<FrameBuffer>(m_Width, m_Height);
		m_ScreenVAO = std::make_unique<VertexArray>();
		m_ScreenVBO = std::make_unique<VertexBuffer>(QUAD_VERTICES, sizeof(QUAD_VERTICES));
		
		VertexBufferLayout layout;
		layout.Push<float>(2, 0);
		layout.Push<float>(2, 0);

		m_ScreenVAO->AddBuffer(*m_ScreenVBO, layout);

		// Framebufferr multisampling
		m_MultisampleBuffer = std::make_unique<FrameBuffer>(m_Width, m_Height, 4);

		// Level Setup
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
		m_Time += deltaTime;
		m_Ball->Move(deltaTime, this->m_Width);
		this->DoCollisions();

		if (m_Ball->position.y >= this->m_Height) // did ball reach bottom edge?
		{
			this->ResetLevel();
			this->ResetPlayer();
		}

		m_Particles->Update(deltaTime, *m_Ball, 2, glm::vec2(m_Ball->radius / 2.0f));

		if (m_ShakeTime > 0.0f)
		{
			m_ShakeTime -= deltaTime;
			if (m_ShakeTime <= 0.0f)
				m_Shake = false;
		}
	}

	void TestGame::OnRender(Renderer& renderer)
	{
		m_SpriteShader->Bind();
		//m_ParticleShader->Bind();
		if (this->state == GAME_ACTIVE)
		{
			m_MultisampleBuffer->Bind();
			m_SpriteRenderer->DrawSprite(*m_Background, glm::vec2(0.0f, 0.0f), glm::vec2(this->m_Width, this->m_Height), 0.0f);

			m_Player->Draw(*m_SpriteRenderer);
			m_Particles->Draw();

			m_SpriteShader->Bind();
			m_Ball->Draw(*m_SpriteRenderer);

			this->Levels[this->Level].Draw(*m_SpriteRenderer);
			
			// Blit the multisample texture
			m_MultisampleBuffer->Bind(GL_READ_FRAMEBUFFER);
			m_ScreenBuffer->Bind(GL_DRAW_FRAMEBUFFER);
			glBlitFramebuffer(0, 0, m_Width, m_Height, 0, 0, m_Width, m_Height, GL_COLOR_BUFFER_BIT, GL_NEAREST);

			m_ScreenBuffer->Unbind();
			m_MultisampleBuffer->Unbind();
			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			glDisable(GL_DEPTH_TEST);

			m_ScreenShader->Bind();
			m_ScreenVAO->Bind();

			m_ScreenBuffer->GetBufferTexture().Bind(0);
			m_ScreenShader->SetInt("screenTexture", 0);
			m_ScreenShader->SetInt("chaos", m_Chaos);
			m_ScreenShader->SetInt("confuse", m_Confuse);
			m_ScreenShader->SetInt("shake", m_Shake);
			m_ScreenShader->SetFloat("time", m_Time);

			renderer.Draw(*m_ScreenVAO, *m_ScreenShader, 6);
		}
	}

	void TestGame::OnImGuiRender()
	{
	}

	void TestGame::DoCollisions()
	{
		for (GameObject& box : this->Levels[this->Level].Bricks)
		{
			if (!box.destroyed)
			{
				Collision::Collided collision = Collision::CheckCollision(*m_Ball, box);
				if (std::get<0>(collision)) // if collision is true
				{
					// destroy block if not solid
					if (!box.isSolid)
						box.destroyed = true;
					//else {
						m_ShakeTime = 0.05;
						m_Shake = true;
					//}

					// collision resolution
					Collision::Direction dir = std::get<1>(collision);
					glm::vec2 diff_vector = std::get<2>(collision);
					if (dir == Collision::Direction::LEFT || dir == Collision::Direction::RIGHT) // horizontal collision
					{
						m_Ball->velocity.x = -m_Ball->velocity.x; // reverse horizontal velocity
						// relocate
						float penetration = m_Ball->radius - std::abs(diff_vector.x);
						if (dir == Collision::Direction::LEFT)
							m_Ball->position.x += penetration; // move ball to right
						else
							m_Ball->position.x -= penetration; // move ball to left;
					}
					else // vertical collision
					{
						m_Ball->velocity.y = -m_Ball->velocity.y; // reverse vertical velocity
						// relocate
						float penetration = m_Ball->radius - std::abs(diff_vector.y);
						if (dir == Collision::Direction::UP)
							m_Ball->position.y -= penetration; // move ball back up
						else
							m_Ball->position.y += penetration; // move ball back down
					}
				}
			}
		}

		Collision::Collided result = Collision::CheckCollision(*m_Ball, *m_Player);
		if (!m_Ball->stuck && std::get<0>(result))
		{
			// check where it hit the board, and change velocity based on where it hit the board
			float centerBoard = m_Player->position.x + m_Player->size.x / 2.0f;
			float distance = (m_Ball->position.x + m_Ball->radius) - centerBoard;
			float percentage = distance / (m_Player->size.x / 2.0f);
			// then move accordingly
			float strength = 2.0f;
			glm::vec2 oldVelocity = m_Ball->velocity;
			m_Ball->velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength;
			m_Ball->velocity.y = -1.0f * abs(m_Ball->velocity.y);
			m_Ball->velocity = glm::normalize(m_Ball->velocity) * glm::length(oldVelocity);
		}
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

	void TestGame::ResetLevel()
	{
		if (this->Level == 0)
			this->Levels[0].Load("res\\Levels\\level01.txt", this->m_Width, this->m_Height / 2);
		else if (this->Level == 1)
			this->Levels[1].Load("res\\Levels\\level02.txt", this->m_Width, this->m_Height / 2);
		else if (this->Level == 2)
			this->Levels[2].Load("res\\Levels\\level03.txt", this->m_Width, this->m_Height / 2);
		else if (this->Level == 3)
			this->Levels[3].Load("res\\Levels\\level04.txt", this->m_Width, this->m_Height / 2);
	}

	void TestGame::ResetPlayer()
	{
		// reset player/ball stats
		m_Player->size = PLAYER_SIZE;
		m_Player->position = glm::vec2(this->m_Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->m_Height - PLAYER_SIZE.y - 20);
		m_Ball->Reset(m_Player->position + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -(BALL_RADIUS * 2.0f)), INITIAL_BALL_VELOCITY);
	}
}
