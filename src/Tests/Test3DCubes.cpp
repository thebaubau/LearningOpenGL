#include "imgui.h"
#include "Renderer.h"
#include "Test3DCubes.h"
#include <Shader.h>


namespace Test {
	glm::vec3 cubePositionss[] = {
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
	float cubeVerticess[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	float deltaTime = 0.0f;	// Time between current frame and last frame
	float lastFrame = 0.0f; // Time of last frame
	float lastX = 1280 / 2.0f;
	float lastY = 920 / 2.0f;
	bool firstMouse = true;

	Test3DCubes::Test3DCubes() {
		Renderer renderer;

		m_VAO = std::make_unique<VertexArray>();
		m_VBO = std::make_unique<VertexBuffer>(cubeVerticess, sizeof(cubeVerticess));
		m_Camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 10.0f));

		VertexBufferLayout layout;

		// First 3 floats from cubeVertices for vertex position
		layout.Push<float>(3);

		// Next 2 floats for textures
		layout.Push<float>(2);

		// Binds vao and vbo. Sets up the attribute pointers for the shader
		m_VAO->AddBuffer(*m_VBO, layout);

		// TEXTURE
		m_Texture1 = std::make_unique<Texture>("res\\Textures\\container.jpg");
		m_Texture2 = std::make_unique<Texture>("res\\Textures\\awesomeface.png");

		m_Shader = std::make_unique<Shader>("res\\Shaders\\VertexShader.glsl", "res\\Shaders\\FragmentShader.glsl");
		m_Shader->Bind();
		m_Shader->SetInt("texture1", 0);
		m_Shader->SetInt("texture2", 1);

		m_Texture1->Bind(0);
		m_Texture2->Bind(1);
	}

	Test3DCubes::~Test3DCubes() {
	}

	void Test3DCubes::OnCreate(Window window) {
		m_Window = window;
		glfwSetWindowUserPointer(window.getWindow(), this);
		glfwSetCursorPosCallback(window.getWindow(), [](GLFWwindow* win, double xpos, double ypos) {
			static_cast<Test3DCubes*>(glfwGetWindowUserPointer(win))->MouseCallback(win, xpos, ypos);
		});
		glfwSetScrollCallback(window.getWindow(), [](GLFWwindow* win, double xoffset, double yoffset) {
			static_cast<Test3DCubes*>(glfwGetWindowUserPointer(win))->ScrollCallback(win, xoffset, yoffset);
		});
	}

	void Test3DCubes::OnUpdate(float deltaTime) {
	}

	void Test3DCubes::OnRender() {
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glClearColor(0.2f, 0.3f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Renderer renderer;

		m_View = m_Camera->GetViewMatrix();
		m_Projection = glm::perspective(glm::radians(m_Camera->Zoom), (float)1280 / (float)920, 0.1f, 100.0f);

		m_Shader->SetMat4("view", m_View);
		m_Shader->SetMat4("projection", m_Projection);
		m_Shader->SetFloat("mixValue", m_MixValue);

		for (unsigned int i = 0; i < 11; i++) {
			float angle = 10 * (i + 1);
			glm::mat4 model = glm::mat4(1.0f);

			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), cubePositionss[i]);
			model = glm::translate(model, glm::vec3(cubePositionss[i]));

			m_Shader->SetMat4("model", model);

			renderer.Draw(*m_VAO, *m_Shader);
		}

		ProcessInput(m_Window.getWindow());
	}

	void Test3DCubes::OnImGuiRender() {

	}

	void Test3DCubes::ProcessInput(GLFWwindow* window) {
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			m_MixValue += 0.005f;
			if (m_MixValue > 1.0f)
				m_MixValue = 1.0f;
		}

		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			m_MixValue -= 0.005f;
			if (m_MixValue < 0.0f)
				m_MixValue = 0.0f;
		}

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
	};

	void Test3DCubes::MouseCallback(GLFWwindow* window, double xposIn, double yposIn) {
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
	};

	void Test3DCubes::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
		m_Camera->ProcessMouseScroll(static_cast<float>(yoffset));
	};
}
