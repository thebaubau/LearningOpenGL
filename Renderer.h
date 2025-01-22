#pragma once
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
#include <iostream>


#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

class Renderer {
private:

public:
	~Renderer() = default;

	void Draw(const VertexArray& va, const Shader& shader) const;
	void Clear() const;
};

