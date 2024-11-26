#pragma once
#include "Camera.h"
#include "Dependencies\stb_image.h"
#include "Shader.h"
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>


class Renderer {
private:
	Shader m_Shader;
	Camera m_Camera;

public:
	Renderer() = default;
	~Renderer() = default;

	void init();
	void update();
	void end();

	Shader getShader() const;
	void setShader(Shader shader);

	Camera getCamera() const;
	void setCamera(Camera camera);
};

