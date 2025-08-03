#include "TestLighting.h"
#include <imgui.h>

namespace Test {
	const float TestLighting::cubeVertices[] = {
				// positions          // normals           // texture coords
				-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
				 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
				 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
				 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
				-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
				-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

				-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
				 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
				 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
				 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
				-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
				-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

				-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
				-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
				-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
				-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
				-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
				-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

				 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
				 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
				 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
				 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
				 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
				 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

				-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
				 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
				 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
				 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
				-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
				-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

				-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
				 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
				 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
				 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
				-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
				-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};
	glm::vec3 TestLighting::cubePositions[] = {
		glm::vec3(0.0f, 0.2f, 0.5f),
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	TestLighting::TestLighting(GLFWwindow* window) {
		m_Window = window;

		m_VAO = std::make_unique<VertexArray>();
		m_VAO_Light = std::make_unique<VertexArray>();

		m_VBO = std::make_unique<VertexBuffer>(cubeVertices, sizeof(cubeVertices));
		//m_EBO = std::make_unique<IndexBuffer>(indices, sizeof(indices));

		m_VertexBufferLayout = std::make_unique<VertexBufferLayout>();
		m_VertexBufferLayout_Light = std::make_unique<VertexBufferLayout>();

		m_Camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 3.7f));
		
		m_DiffuseTexture = std::make_unique<Texture>("res\\Textures\\container2.png");
		m_SpecularTexture = std::make_unique<Texture>("res\\Textures\\container2_specular.png");
		m_EmissionTexture = std::make_unique<Texture>("res\\Textures\\matrix.jpg");

		m_LightSourceShader = std::make_unique<Shader>("res\\Shaders\\SimpleVertexShader.glsl", "res\\Shaders\\SimpleFragShader.glsl");
		m_LightingShader = std::make_unique<Shader>("res\\Shaders\\LightingVertexShader.glsl", "res\\Shaders\\LightingFragShader.glsl");

		// First three for position
		m_VertexBufferLayout->Push<float>(3, 0);

		// Next three for normals
		m_VertexBufferLayout->Push<float>(3, 0);

		// Texture
		m_VertexBufferLayout->Push<float>(2, 0);
		
		m_VertexBufferLayout_Light->Push<float>(3, 0);
		m_VertexBufferLayout_Light->Push<float>(3, 0);
		m_VertexBufferLayout_Light->Push<float>(2, 0);

		m_VAO->AddBuffer(*m_VBO, *m_VertexBufferLayout);
		m_VAO_Light->AddBuffer(*m_VBO, *m_VertexBufferLayout_Light);

		// Texture binding
		m_LightingShader->Bind();
		m_LightingShader->SetInt("material.diffuse", 0);
		m_LightingShader->SetInt("material.specular", 1);
		m_LightingShader->SetInt("material.emission", 2);

		m_DiffuseTexture->Bind(0);
		m_SpecularTexture->Bind(1);
		m_EmissionTexture->Bind(2);
	}

	void TestLighting::OnCreate() {}

	void TestLighting::OnUpdate(float deltaTime) {
		//glfwSetWindowUserPointer(m_Window, this);
		//glfwSetCursorPosCallback(m_Window, [](GLFWwindow* win, double xpos, double ypos) {
		//	static_cast<TestLighting*>(glfwGetWindowUserPointer(win))->MouseCallback(win, xpos, ypos);
		//});
		//glfwSetScrollCallback(m_Window, [](GLFWwindow* win, double xoffset, double yoffset) {
		//	static_cast<TestLighting*>(glfwGetWindowUserPointer(win))->ScrollCallback(win, xoffset, yoffset);
		//});

		//ProcessInput(m_Window);
	}

	void TestLighting::OnRender() {
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Renderer renderer;

		// ###################
		// Light Source Cube #
		// ###################

		glm::vec3 lightColor;
		lightColor.x = 0.5f + 0.5f * sin(glfwGetTime() * 2.0f);
		lightColor.y = 0.5f + 0.5f * sin(glfwGetTime() * 0.7f);
		lightColor.z = 0.5f + 0.5f * sin(glfwGetTime() * 1.3f);

		glm::vec3 ambientColor = lightColor * glm::vec3(0.2f);
		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
		glm::vec3 specularColor = lightColor * glm::vec3(1.0f);

		m_View = m_Camera->GetViewMatrix();
		m_Projection = glm::perspective(glm::radians(m_Camera->Zoom), (float)1280 / (float)920, 0.1f, 100.0f);

		m_LightSourceShader->Bind();
		m_LightSourceShader->SetMat4("view", m_View);
		m_LightSourceShader->SetMat4("projection", m_Projection);
		m_LightSourceShader->SetVec3("objectColor", lightColor);

		glm::mat4 model = glm::mat4(1.0f);
		//cubePositions[1].x = 1.0f + sin(glfwGetTime()) * 2.0f;
		//cubePositions[1].y = sin(glfwGetTime() / 2.0f) * 1.0f;

		float radius = 2.0f;
		float time = glfwGetTime();
		cubePositions[1].x = cubePositions[0].x + cos(time) * radius;
		cubePositions[1].z = cubePositions[0].z + sin(time) * radius;
		cubePositions[1].y = sin(time / 1.0f) * 0.5f;

		model = glm::translate(model, cubePositions[1]);
		model = glm::scale(model, glm::vec3(0.2f));
		//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(5.0f), cubePositions[1]);

		m_LightSourceShader->SetMat4("model", model);

		//renderer.Draw(*m_VAO, *m_LightSourceShader, 36);

		// ###################
		// Light Source Cube #
		// ###################

		// ##############
		// Texture Cube #
		// ##############

		m_LightingShader->Bind();

		// Use these when no texture
		//m_LightingShader->SetVec3("objectColor", 1.0f, 0.5f, 0.31f);
		//m_LightingShader->SetVec3("material.ambient", 1.0f, 0.5f, 0.31f);
		//m_LightingShader->SetVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
		//m_LightingShader->SetVec3("material.specular", 0.5f, 0.5f, 0.5f);

		m_LightingShader->SetFloat("material.shininess", 64.0f);

		// Use these for disco lights
		//m_LightingShader->SetVec3("light.ambient", ambientColor);
		//m_LightingShader->SetVec3("light.diffuse", diffuseColor);
		//m_LightingShader->SetVec3("light.specular", specularColor);

		// Use these for normal directional light
		m_LightingShader->SetVec3("light.ambient", glm::vec3(0.2f));
		m_LightingShader->SetVec3("light.diffuse", glm::vec3(0.5f));
		m_LightingShader->SetVec3("light.specular", glm::vec3(1.0f));

		m_LightingShader->SetFloat("light.constant", 1.0f);
		m_LightingShader->SetFloat("light.linear", 0.09f);
		m_LightingShader->SetFloat("light.quadratic", 0.032f);

		m_LightingShader->SetVec3("light.position", cubePositions[1]);
		m_LightingShader->SetVec3("light.direction", glm::vec3(-0.2f, -1.0f, -0.3f));

		m_LightingShader->SetVec3("viewPos", m_Camera->Position);
		m_LightingShader->SetMat4("view", m_View);
		m_LightingShader->SetMat4("projection", m_Projection);

		for (unsigned int i{ 2 }; i < 11; i++) {
			model = glm::mat4(1.0f);

			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(10.0f * i), cubePositions[i]);
			//model = glm::scale(model, glm::vec3(2.0f));
			m_LightingShader->SetMat4("model", model);
			renderer.Draw(*m_VAO_Light, *m_LightingShader, 36);
		}
		model = glm::mat4(1.0f);

		model = glm::translate(model, glm::vec3(cubePositions[0]));
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(10.0f), cubePositions[0]);
		//model = glm::scale(model, glm::vec3(2.0f));
		//glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(model)));

		m_LightingShader->SetMat4("model", model);
		//m_LightingShader->SetMat3("normalMatrix", normalMatrix);
		//m_DiffuseTexture->Bind(0);
		renderer.Draw(*m_VAO_Light, *m_LightingShader, 36);

		// ##############
		// Texture Cube #
		// ##############
	}

	void TestLighting::OnImGuiRender() {
		ImGui::Begin("Light Position");

		ImGui::DragFloat3("Light Pos", &cubePositions[1][0], 0.1f);
		ImGui::DragFloat3("Cube Movement", &cubePositions[0][0], 0.1f);

		ImGui::End();
	}

	void TestLighting::ProcessInput(GLFWwindow* window)	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			m_Camera->ProcessKeyboard(FORWARD, deltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			m_Camera->ProcessKeyboard(BACKWARD, deltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			m_Camera->ProcessKeyboard(LEFT, deltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			m_Camera->ProcessKeyboard(RIGHT, deltaTime);
		}
	}

	void TestLighting::MouseCallback(GLFWwindow* window, double xposIn, double yposIn) {
		float xpos = static_cast<float>(xposIn);
		float ypos = static_cast<float>(yposIn);

		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

		lastX = xpos;
		lastY = ypos;

		m_Camera->ProcessMouseMovement(xoffset, yoffset);
	}

	void TestLighting::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
		m_Camera->ProcessMouseScroll(static_cast<float>(yoffset));
	}
}