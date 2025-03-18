#include "TestLighting.h"

namespace Test {
	glm::vec3 coral{ 1.0f, 0.5f, 0.31f };

	//float deltaTime = 0.0f;	// Time between current frame and last frame
	//float lastFrame = 0.0f; // Time of last frame
	//float lastX = 1280 / 2.0f;
	//float lastY = 920 / 2.0f;

	glm::mat4 m_View = glm::mat4(1.0f);
	glm::mat4 m_Projection = glm::mat4(1.0f);

	float cubeVertices[] = {
		// Front face
		0.5f,  0.5f,  0.5f,  // Top right
		0.5f, -0.5f,  0.5f,  // Bottom right
	   -0.5f, -0.5f,  0.5f,  // Bottom left
	   -0.5f,  0.5f,  0.5f,  // Top left

	   // Back face
	   0.5f,  0.5f, -0.5f,  // Top right
	   0.5f, -0.5f, -0.5f,  // Bottom right
	  -0.5f, -0.5f, -0.5f,  // Bottom left
	  -0.5f,  0.5f, -0.5f   // Top left
	};

	unsigned int indices[] = {
		// Front face
		0, 1, 3,
		1, 2, 3,

		// Back face
		4, 5, 7,
		5, 6, 7,

		// Left face
		3, 2, 7,
		2, 6, 7,

		// Right face
		0, 1, 4,
		1, 5, 4,

		// Top face
		0, 3, 4,
		3, 7, 4,

		// Bottom face
		1, 2, 5,
		2, 6, 5
	};

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f, 0.2f, 0.5f)
	};

	TestLighting::TestLighting(GLFWwindow* window) {
		m_Window = window;
		m_VAO = std::make_unique<VertexArray>();
		m_VBO = std::make_unique<VertexBuffer>(cubeVertices, sizeof(cubeVertices));
		m_EBO = std::make_unique<IndexBuffer>(indices, sizeof(indices));
		m_VertexBufferLayout = std::make_unique<VertexBufferLayout>();
		m_Camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 10.0f));
		m_Shader = std::make_unique<Shader>("res\\Shaders\\VertexShader.glsl", "res\\Shaders\\FragmentShader.glsl");

		m_VertexBufferLayout->Push<float>(3);
		m_VAO->AddBuffer(*m_VBO, *m_VertexBufferLayout);

		m_Shader->Bind();
	}

	void TestLighting::OnCreate() {}

	void TestLighting::OnUpdate(float deltaTime) {

	}

	void TestLighting::OnRender() {
		glClearColor(0.2f, 0.3f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Renderer renderer;

		m_View = m_Camera->GetViewMatrix();
		m_Projection = glm::perspective(glm::radians(m_Camera->Zoom), (float)1280 / (float)920, 0.1f, 100.0f);

		m_Shader->SetMat4("view", m_View);
		m_Shader->SetMat4("projection", m_Projection);

		glm::mat4 model = glm::mat4(1.0f);

		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(5.0f), cubePositions[0]);
		model = glm::translate(model, glm::vec3(cubePositions[0]));

		m_Shader->SetMat4("model", model);

		renderer.Draw(*m_VAO, *m_Shader, 36);
	}

	void TestLighting::OnImGuiRender() {

	}



}