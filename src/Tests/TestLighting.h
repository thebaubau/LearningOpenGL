#pragma once
#include "Test.h"
#include <Camera.h>
#include <glm\glm.hpp>
#include <VertexArray.h>
#include <VertexBuffer.h>
#include <VertexBufferLayout.h>

namespace Test {
	class TestLighting : public Test {

		int counter = 1;

	public:
		TestLighting(GLFWwindow* window);
		~TestLighting() = default;

		void OnCreate() override;
		void OnUpdate(float deltaTime) override;

		void OnRender() override;
		void OnImGuiRender() override;
	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexArray> m_VAO_Light;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<IndexBuffer> m_EBO;
		std::unique_ptr<VertexBufferLayout> m_VertexBufferLayout;
		std::unique_ptr<VertexBufferLayout> m_VertexBufferLayout_Light;
		std::unique_ptr<Shader> m_LightSourceShader;
		std::unique_ptr<Shader> m_LightingShader;
		std::unique_ptr<Camera> m_Camera;

		static const float cubeVertices[36 * 6];
		static glm::vec3 cubePositions[2];


		//static unsigned int indices[6] = {
		//	0, 1, 3,
		//	1, 2, 3
		//};
		
		glm::vec3 lightColor{ 1.0f, 1.0f, 1.0f };
		glm::vec3 objectColor{ 1.0f, 0.5f, 0.31f };

		glm::mat4 m_View = glm::mat4(1.0f);
		glm::mat4 m_Projection = glm::mat4(1.0f);

		float deltaTime = 0.0f;	// Time between current frame and last frame
		float lastFrame = 0.0f; // Time of last frame
		float lastX = 1280 / 2.0f;
		float lastY = 920 / 2.0f;
		bool firstMouse = true;
		float cubeRotation{ 20.0f };

		GLFWwindow* m_Window;

		void ProcessInput(GLFWwindow* window);

		void MouseCallback(GLFWwindow* window, double xposIn, double yposIn);

		void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	};

}

