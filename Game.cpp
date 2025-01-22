#include "Camera.h"
#include "Dependencies\stb_image.h"
#include "Game.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 920;

float mixValue{ 0.2f };
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

float lastX = SCREEN_WIDTH / 2.0f;
float lastY = SCREEN_HEIGHT / 2.0f;
bool firstMouse = true;

glm::vec3 cubePositions[] = {
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

float cubeVertices[] = {
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

float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };

Camera m_Camera(glm::vec3(0.0f, 0.0f, 3.0f));

void processInput(GLFWwindow* window);

void mouseCallback(GLFWwindow* window, double xposIn, double yposIn);

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

void Game::Init() {
	window.setScreenWidth(SCREEN_WIDTH);
	window.setScreenHeight(SCREEN_HEIGHT);
	window.setWindowName("Learning OpenGL");

	window.init();

	glfwSetCursorPosCallback(window.getWindow(), mouseCallback);
	glfwSetScrollCallback(window.getWindow(), scrollCallback);

	Shader m_Shader("VertexShader.glsl", "FragmentShader.glsl");
	Renderer renderer;

	VertexArray vao;
	VertexBuffer vbo(cubeVertices, sizeof(cubeVertices));

	VertexBufferLayout layout;

	// First 3 floats from cubeVertices for vertex position
	layout.Push<float>(3);

	// Next 2 floats for textures
	layout.Push<float>(2);

	// Binds vao and vbo. Sets up the attribute pointers for the shader
	vao.AddBuffer(vbo, layout);

	// Done with VAO
	vao.Unbind();

	// Done with VBO
	vbo.Unbind();

	// TEXTURE
	Texture texture1("Textures/container.jpg");
	Texture texture2("Textures/awesomeface.png");

	m_Shader.Bind();
	m_Shader.SetInt("texture1", 0);
	m_Shader.SetInt("texture2", 1);

	std::cout << "Game running" << std::endl;

	auto gameWindow = window.getWindow();

	double currentTime;
	double previousTime;

	texture1.Bind(0);
	texture2.Bind(1);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	while (!glfwWindowShouldClose(gameWindow))
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(gameWindow);

		window.update();

		// Background
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		renderer.Clear();

		m_Shader.Bind();

		glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		view = m_Camera.GetViewMatrix();
		projection = glm::perspective(glm::radians(m_Camera.Zoom), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

		m_Shader.SetMat4("model", model);
		m_Shader.SetMat4("view", view);
		m_Shader.SetMat4("projection", projection);
		m_Shader.SetFloat("mixValue", mixValue);

		//glDrawArrays(GL_TRIANGLES, 0, 36);
		renderer.Draw(vao, m_Shader);

		for (unsigned int i = 0; i < 10; i++)
		{
			float angle = 10 * i;
			glm::mat4 model = glm::mat4(1.0f);

			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), cubePositions[i]);
			model = glm::translate(model, glm::vec3(cubePositions[i]));

			m_Shader.SetMat4("model", model);

			renderer.Draw(vao, m_Shader);
		}

		//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}

	vao.Unbind();
	vbo.Unbind();
	m_Shader.Unbind();
}

void Game::End() {
	std::cout << "Game Ended" << std::endl;
	glfwTerminate();
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		mixValue += 0.005f;
		if (mixValue > 1.0f)
			mixValue = 1.0f;
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		mixValue -= 0.005f;
		if (mixValue < 0.0f)
			mixValue = 0.0f;
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		m_Camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		m_Camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		m_Camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		m_Camera.ProcessKeyboard(RIGHT, deltaTime);
};

void mouseCallback(GLFWwindow* window, double xposIn, double yposIn) {
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

	m_Camera.ProcessMouseMovement(xoffset, yoffset);
};

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	m_Camera.ProcessMouseScroll(static_cast<float>(yoffset));
};

