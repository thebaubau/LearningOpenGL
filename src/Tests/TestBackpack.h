#pragma once

#include "Test.h"
#include <GLFW/glfw3.h>
#include "Model.h"
#include <imgui.h>
#include <Camera.h>
#include <iostream>

namespace Test 
{
	class TestBackpack : public Test
	{
	public:
		TestBackpack(GLFWwindow* window);
		~TestBackpack();

		void OnCreate() override;
		void OnUpdate(float deltaTime) override;
		void OnRender(Renderer& renderer) override;
		void OnImGuiRender() override;

	private:

		std::unique_ptr<Model> m_Backpack;
		std::unique_ptr<Camera> m_Camera;
		std::unique_ptr<Shader> m_Shader;

		static const float vertices[108];
		std::vector<std::string> faces = {
			"right.jpg",
			"left.jpg",
			"top.jpg",
			"bottom.jpg",
			"front.jpg",
			"back.jpg"
		};

		float deltaTime = 0.0f;
		float lastX = 1280 / 2.0f;
		float lastY = 920 / 2.0f;
		bool firstMouse = true;

		glm::mat4 m_View = glm::mat4(1.0f);
		glm::mat4 m_Projection = glm::mat4(1.0f);

		GLFWwindow* m_Window;
		GLFWcursorposfun m_PrevCursorPosCallback = nullptr;
		GLFWscrollfun m_PrevScrollCallback = nullptr;

		void ProcessInput(GLFWwindow* window);

		void MouseCallback(GLFWwindow* window, double xposIn, double yposIn);

		void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	};
}
