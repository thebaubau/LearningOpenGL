#pragma once

#include "Camera.h"
#include "Test.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace Test {
	class Test3DCubes : public Test {
	public:
		Test3DCubes();
		~Test3DCubes();

		void OnCreate(Window window) override;
		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture1;
		std::unique_ptr<Texture> m_Texture2;
		std::unique_ptr<Camera> m_Camera;

		glm::mat4 m_View = glm::mat4(1.0f);
		glm::mat4 m_Projection = glm::mat4(1.0f);
		float m_MixValue{ 0.2f };
		Window m_Window;

		void ProcessInput(GLFWwindow* window);

		void MouseCallback(GLFWwindow* window, double xposIn, double yposIn);

		void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	};
}