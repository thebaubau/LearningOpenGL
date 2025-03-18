#pragma once
#include "Test.h"
#include <Camera.h>
#include <glm\glm.hpp>
#include <VertexArray.h>
#include <VertexBuffer.h>
#include <VertexBufferLayout.cpp>

namespace Test {
	class TestLighting : public Test {
	public:
		TestLighting(GLFWwindow* window);
		~TestLighting() = default;

		void OnCreate() override;
		void OnUpdate(float deltaTime) override;

		void OnRender() override;
		void OnImGuiRender() override;
	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<IndexBuffer> m_EBO;
		std::unique_ptr<VertexBufferLayout> m_VertexBufferLayout;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Camera> m_Camera;

		GLFWwindow* m_Window;
	};

}

