#include "TestLighting.h"

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
	std::array<glm::vec3, 11> TestLighting::cubePositions = {
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

	std::array<glm::vec3, 4> TestLighting::pointLightPositions = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};

	glm::vec3 ambientColorIntensity = glm::vec3(0.2f);
	glm::vec3 diffuseColorIntensity = glm::vec3(0.7f);
	glm::vec3 specularColorIntensity = glm::vec3(1.0f);

	TestLighting::TestLighting(GLFWwindow* window) {
		m_Window = window;

		m_VAO = std::make_unique<VertexArray>();
		m_VAO_Light = std::make_unique<VertexArray>();

		m_VBO = std::make_unique<VertexBuffer>(cubeVertices, sizeof(cubeVertices));
		//m_EBO = std::make_unique<IndexBuffer>(indices, sizeof(indices));

		m_VertexBufferLayout = std::make_unique<VertexBufferLayout>();
		m_VertexBufferLayout_Light = std::make_unique<VertexBufferLayout>();

		m_Camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 3.7f));
		
		m_DiffuseTexture = std::make_unique<Texture>("res\\Textures\\container2.png", "diffuse");
		m_SpecularTexture = std::make_unique<Texture>("res\\Textures\\container2_specular.png", "specular");
		m_EmissionTexture = std::make_unique<Texture>("res\\Textures\\matrix.jpg", "diffuse");

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

		// Store ImGui's callbacks and set ours
		glfwSetWindowUserPointer(m_Window, this);
		m_PrevCursorPosCallback = glfwSetCursorPosCallback(m_Window, [](GLFWwindow* win, double xpos, double ypos) {
			auto* self = static_cast<TestLighting*>(glfwGetWindowUserPointer(win));
			// Call ImGui's callback first
			if (self->m_PrevCursorPosCallback)
				self->m_PrevCursorPosCallback(win, xpos, ypos);
			// Then call ours
			self->MouseCallback(win, xpos, ypos);
			});

		m_PrevScrollCallback = glfwSetScrollCallback(m_Window, [](GLFWwindow* win, double xoffset, double yoffset) {
			auto* self = static_cast<TestLighting*>(glfwGetWindowUserPointer(win));
			// Call ImGui's callback first
			if (self->m_PrevScrollCallback)
				self->m_PrevScrollCallback(win, xoffset, yoffset);
			// Then call ours
			self->ScrollCallback(win, xoffset, yoffset);
			});
	}

	TestLighting::~TestLighting() {
		// Restore ImGui's callbacks when destroying
		if (m_PrevCursorPosCallback)
			glfwSetCursorPosCallback(m_Window, m_PrevCursorPosCallback);
		if (m_PrevScrollCallback)
			glfwSetScrollCallback(m_Window, m_PrevScrollCallback);
	}

	void TestLighting::OnCreate() {}

	void TestLighting::OnUpdate(float deltaTime) {
		this->deltaTime = deltaTime;
		
		ProcessInput(m_Window);
	}

	void TestLighting::OnRender(Renderer& renderer) {
		glClearColor(0.0f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Renderer renderer;

		// ###################
		// Light Source Cube #
		// ###################

		glm::vec3 lightColor;
		glm::vec3 dirLightColor;

		// Disco light colors
		//lightColor.x = 0.5f + 0.5f * sin(glfwGetTime() * 2.0f);
		//lightColor.y = 0.5f + 0.5f * sin(glfwGetTime() * 0.7f);
		//lightColor.z = 0.5f + 0.5f * sin(glfwGetTime() * 1.3f);

		dirLightColor = glm::vec3(0.1f);

		// Normal white light
		lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

		glm::vec3 ambientColor = lightColor * ambientColorIntensity;
		glm::vec3 diffuseColor = lightColor * diffuseColorIntensity;
		glm::vec3 specularColor = lightColor * specularColorIntensity;

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

		for (unsigned int i{ 0 }; i < pointLightPositions.size(); i++) {
			pointLightPositions[i].x = cubePositions[i].x + cos(time * 0.5f + i) * radius;
			pointLightPositions[i].z = cubePositions[i].z + sin(time * 0.5f + i) * radius;
			pointLightPositions[i].y = sin(time / 1.0f + i);

			model = glm::mat4(1.0f);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f));
			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(5.0f), pointLightPositions[i]);
			m_LightSourceShader->SetMat4("model", model);

			renderer.Draw(*m_VAO, *m_LightSourceShader, 36);
		}

		//cubePositions[1].x = cubePositions[0].x + cos(time * 0.2f) * radius;
		//cubePositions[1].z = cubePositions[0].z + sin(time * 0.2f) * radius;
		//cubePositions[1].y = sin(time / 1.0f);

		//model = glm::translate(model, cubePositions[1]);
		//model = glm::scale(model, glm::vec3(0.2f));
		//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(5.0f), cubePositions[1]);


		// ###################
		// Light Source Cube #
		// ###################


		// ##############
		// Texture Cube #
		// ##############

		m_LightingShader->Bind();

		// Use these when no texture is assigned
		//m_LightingShader->SetVec3("objectColor", 1.0f, 0.5f, 0.31f);
		//m_LightingShader->SetVec3("material.ambient", 1.0f, 0.5f, 0.31f);
		//m_LightingShader->SetVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
		//m_LightingShader->SetVec3("material.specular", 0.5f, 0.5f, 0.5f);

		m_LightingShader->SetFloat("material.shininess", 64.0f);

		for (int i{ 0 }; i < pointLightPositions.size(); i++) {
			// Point lights
			std::string number = std::to_string(i);
			m_LightingShader->SetVec3("pointLights[" + number + "].position", pointLightPositions[i]);

			m_LightingShader->SetVec3("pointLights[" + number + "].ambient", ambientColor);
			m_LightingShader->SetVec3("pointLights[" + number + "].diffuse", diffuseColor);
			m_LightingShader->SetVec3("pointLights[" + number + "].specular", specularColor);

			m_LightingShader->SetFloat("pointLights[" + number + "].constant", 1.0f);
			m_LightingShader->SetFloat("pointLights[" + number + "].linear", 0.09f);
			m_LightingShader->SetFloat("pointLights[" + number + "].quadratic", 0.032f);
		}

		// Directional Light
		m_LightingShader->SetVec3("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
		m_LightingShader->SetVec3("dirLight.ambient", dirLightColor);
		m_LightingShader->SetVec3("dirLight.diffuse", dirLightColor);
		m_LightingShader->SetVec3("dirLight.specular", dirLightColor);

		// Spotlight (flashlight)
		m_LightingShader->SetVec3("spotLight.position", m_Camera->Position);
		m_LightingShader->SetVec3("spotLight.direction", m_Camera->Front);
		m_LightingShader->SetFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
		m_LightingShader->SetFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
		m_LightingShader->SetVec3("spotLight.ambient", ambientColor);
		m_LightingShader->SetVec3("spotLight.diffuse", diffuseColor);\
		m_LightingShader->SetVec3("spotLight.specular", specularColor);
		m_LightingShader->SetFloat("spotLight.constant", 1.0f);
		m_LightingShader->SetFloat("spotLight.linear", 0.09f);
		m_LightingShader->SetFloat("spotLight.quadratic", 0.032f);

		// MVP
		m_LightingShader->SetVec3("viewPos", m_Camera->Position);
		m_LightingShader->SetMat4("view", m_View);
		m_LightingShader->SetMat4("projection", m_Projection);

		for (unsigned int i = 0; i < cubePositions.size(); i++) {
			model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(10.0f * (i + 1)), cubePositions[i]);
			
			// Calculate normal matrix for correct lighting on the CPU side
			glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(model)));

			m_LightingShader->SetMat4("model", model);
			m_LightingShader->SetMat3("normalMatrix", normalMatrix);
			
			renderer.Draw(*m_VAO_Light, *m_LightingShader, 36);
		}

		// ##############
		// Texture Cube #
		// ##############
	}

	void TestLighting::OnImGuiRender() {
		ImGui::Begin("Light Position");

		ImGui::DragFloat3("Light Pos", &cubePositions[1][0], 0.1f);
		ImGui::DragFloat3("Cube Movement", &cubePositions[0][0], 0.1f);
		ImGui::DragFloat3("Ambient Color", &ambientColorIntensity[0], 0.1f);
		ImGui::DragFloat3("Diffuse Color", &diffuseColorIntensity[0]);
		ImGui::DragFloat3("Specular Color", &specularColorIntensity[0]);

		ImGui::End();
	}

	void TestLighting::ProcessInput(GLFWwindow* window) {
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
		ImGuiIO& io = ImGui::GetIO();
		if (io.WantCaptureMouse) {
			firstMouse = true;  // Reset to avoid camera jump
			return;
		}

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
		ImGuiIO& io = ImGui::GetIO();
		if (io.WantCaptureMouse)
			return;

		m_Camera->ProcessMouseScroll(static_cast<float>(yoffset));
	}
}