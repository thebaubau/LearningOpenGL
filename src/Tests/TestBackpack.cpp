#include "TestBackpack.h"

namespace Test {

	const float TestBackpack::vertices[] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};

	TestBackpack::TestBackpack(GLFWwindow* window)
	{
		m_Window = window;

		m_Backpack = std::make_unique<Model>("I:\\Projects\\CPP\\OpenGLGame\\res\\Textures\\backpack\\backpack.obj");
		m_Shader = std::make_unique<Shader>("res\\Shaders\\VertexBackpack.glsl", "res\\Shaders\\FragmentBackpack.glsl");
		m_SkyboxShader = std::make_unique<Shader>("res\\Shaders\\SkyboxVertexShader.glsl", "res\\Shaders\\SkyboxFragShader.glsl");

		m_SkyboxVAO = std::make_unique<VertexArray>();
		m_SkyboxVBO = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));

		VertexBufferLayout layout;

		layout.Push<float>(3, 0);

		m_SkyboxVAO->AddBuffer(*m_SkyboxVBO, layout);

		m_Skybox = std::make_unique<Cubemap>(
			CubemapFaces{
				.right = "res/Textures/skybox/right.jpg",
				.left = "res/Textures/skybox/left.jpg",
				.top = "res/Textures/skybox/top.jpg",
				.bottom = "res/Textures/skybox/bottom.jpg",
				.front = "res/Textures/skybox/front.jpg",
				.back = "res/Textures/skybox/back.jpg"
			});;

		m_Camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 7.7f));

		glfwSetWindowUserPointer(m_Window, this);
		m_PrevCursorPosCallback = glfwSetCursorPosCallback(m_Window, [](GLFWwindow* win, double xpos, double ypos) {
			auto* self = static_cast<TestBackpack*>(glfwGetWindowUserPointer(win));
			// Call ImGui's callback first
			if (self->m_PrevCursorPosCallback)
				self->m_PrevCursorPosCallback(win, xpos, ypos);
			// Then call ours
			self->MouseCallback(win, xpos, ypos);
			});

		m_PrevScrollCallback = glfwSetScrollCallback(m_Window, [](GLFWwindow* win, double xoffset, double yoffset) {
			auto* self = static_cast<TestBackpack*>(glfwGetWindowUserPointer(win));
			// Call ImGui's callback first
			if (self->m_PrevScrollCallback)
				self->m_PrevScrollCallback(win, xoffset, yoffset);
			// Then call ours
			self->ScrollCallback(win, xoffset, yoffset);
			});
	}

	TestBackpack::~TestBackpack() {
    // Clear window user pointer FIRST to prevent callbacks from accessing dying object
    glfwSetWindowUserPointer(m_Window, nullptr);
    
    // Set callbacks to nullptr to prevent any invocation
    glfwSetCursorPosCallback(m_Window, nullptr);
    glfwSetScrollCallback(m_Window, nullptr);
    
    // Now safe to restore previous callbacks (won't use 'this' anymore)
    if (m_PrevCursorPosCallback)
        glfwSetCursorPosCallback(m_Window, m_PrevCursorPosCallback);
    if (m_PrevScrollCallback)
        glfwSetScrollCallback(m_Window, m_PrevScrollCallback);
}

	void TestBackpack::OnCreate()
	{
		
	}

	//void TestBackpack::ProcessInput(float deltaTime)
	//{
	//}

	void TestBackpack::OnUpdate(float deltaTime)
	{
		this->deltaTime = deltaTime;

		ProcessInput(m_Window);
	}

	void TestBackpack::OnRender(Renderer& renderer)
	{
		glClearColor(0.0f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::vec3 lightPos{ 5.0f, 5.0f, 5.9f };
		//float time = glfwGetTime();

		//lightPos.x = cos(time * 0.5f + 1) * 20.0f;
		//lightPos.z = sin(time * 0.5f + 2) * 20.0f;
		//lightPos.y = sin(time / 1.0f + 3);

		m_View = m_Camera->GetViewMatrix();
		m_Projection = glm::perspective(glm::radians(m_Camera->Zoom), (float)1280 / (float)920, 0.1f, 100.0f);

		m_Shader->Bind();
		m_Shader->SetMat4("view", m_View);
		m_Shader->SetMat4("projection", m_Projection);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		m_Shader->SetMat4("model", model);
		
		// Calculate normal matrix on CPU once per object
		glm::mat3 normalMatrix = glm::mat3(glm::transpose(glm::inverse(model)));
		m_Shader->SetMat3("normalMatrix", normalMatrix);
		
		m_Shader->SetVec3("viewPos", m_Camera->Position);
		m_Shader->SetVec3("lightPos", lightPos);
		m_Shader->SetVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));

		m_Skybox->Bind(m_Backpack->m_LoadedTextures.size());
		m_Shader->SetInt("skybox", m_Backpack->m_LoadedTextures.size());

		m_Backpack->Draw(*m_Shader);

		glDepthFunc(GL_LEQUAL);
		m_SkyboxShader->Bind();
		m_SkyboxShader->SetMat4("view", glm::mat4(glm::mat3(m_Camera->GetViewMatrix())));
		m_SkyboxShader->SetMat4("projection", m_Projection);

		m_Skybox->Bind();
		renderer.Draw(*m_SkyboxVAO, *m_SkyboxShader, sizeof(vertices) / (sizeof(float) * 3));
		glDepthFunc(GL_LESS);
	}

	void TestBackpack::OnImGuiRender()
	{
	}

	void TestBackpack::ProcessInput(GLFWwindow* window) {
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
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		else {
			glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}

	}

	void TestBackpack::MouseCallback(GLFWwindow* window, double xposIn, double yposIn) {
		ImGuiIO& io = ImGui::GetIO();
		if (io.WantCaptureMouse || glfwGetInputMode(m_Window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL) {
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

	void TestBackpack::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
		ImGuiIO& io = ImGui::GetIO();
		if (io.WantCaptureMouse)
			return;

		m_Camera->ProcessMouseScroll(static_cast<float>(yoffset));
	}
}