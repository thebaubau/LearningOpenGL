#include "TestLighting.h"

namespace Test {
	glm::vec3 coral{ 1.0f, 0.5f, 0.31f };

	float cubeVerticies[] = {
		0.5f,  0.5f, 0.5f,    // top right
		0.5f, -0.5f, -0.5f,   // bottom right
		-0.5f, -0.5f, -0.5f,  // bottom left
		-0.5f,  0.5f, -0.5f   // top left 
	};

	unsigned int indices[] = {
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	TestLighting::TestLighting(GLFWwindow* window) {
		m_Window = window;
		m_VAO = std::make_unique<VertexArray>();
		m_VBO = std::make_unique<VertexBuffer>(cubeVerticies, sizeof(cubeVerticies));
		m_EBO = std::make_unique<IndexBuffer>(indices, sizeof(indices));
		m_VertexBufferLayout = std::make_unique<VertexBufferLayout>();
		m_Camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 10.0f));
		m_Shader = std::make_unique<Shader>("res\\Shaders\\VertexShader.glsl", "res\\Shaders\\FragmentShader.glsl");
	}

	void TestLighting::OnCreate() {


	}

	void TestLighting::OnUpdate(float deltaTime) {

	}

	void TestLighting::OnRender() {

	}

	void TestLighting::OnImGuiRender() {

	}



}