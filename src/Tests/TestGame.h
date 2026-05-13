#pragma once

#include "miniaudio.h"
#include <stb_image.h>
#include "SpriteRenderer.h"
#include "Test.h"
#include "Texture.h"
#include "GameObject.h"
#include "GameLevel.h"
#include "BallObject.h"
#include "Collision.h"
#include "ParticleGenerator.h"
#include "FrameBuffer.h"
#include "PowerUp.h"

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
		void DoCollisions();

		ma_result result;
		ma_engine engine;

		std::vector<GameLevel> Levels;
		unsigned int Level;

		int m_Width, m_Height;
		GameState state;
		bool Keys[1024];

		std::vector<PowerUp> PowerUps;
		void SpawnPowerUps(GameObject& block);
		void UpdatePowerUps(float deltaTime);
		void ActivatePowerUp(PowerUp& powerUp);

		bool m_Shake = false, m_Chaos = false, m_Confuse = false;
		float m_ShakeTime = 0.0f;
		float m_Time = 0.0f;

		std::unique_ptr<GameObject> m_Player;
		std::unique_ptr<BallObject> m_Ball;

		std::unique_ptr<Shader> m_SpriteShader;
		std::unique_ptr<Shader> m_ParticleShader;
		std::unique_ptr<Shader> m_ScreenShader;
		std::unique_ptr<SpriteRenderer> m_SpriteRenderer;
		std::unique_ptr<ParticleGenerator> m_Particles;

		std::shared_ptr<Texture> m_Face;
		std::shared_ptr<Texture> m_Background;
		std::shared_ptr<Texture> m_Paddle;
		std::shared_ptr<Texture> m_ParticleTexture;
		std::shared_ptr<Texture> m_TexSpeed;
		std::shared_ptr<Texture> m_TexSticky;
		std::shared_ptr<Texture> m_TexPass;
		std::shared_ptr<Texture> m_TexSize;
		std::shared_ptr<Texture> m_TexConfuse;
		std::shared_ptr<Texture> m_TexChaos;

		std::unique_ptr<FrameBuffer> m_ScreenBuffer;
		std::unique_ptr<FrameBuffer> m_MultisampleBuffer;
		std::unique_ptr<VertexArray> m_ScreenVAO;
		std::unique_ptr<VertexBuffer> m_ScreenVBO;

	private:
		void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

		void ResetLevel();

		void ResetPlayer();

		GLFWwindow* m_Window;
	};
}

