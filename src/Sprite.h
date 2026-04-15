#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <Texture.h>
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"

class Sprite
{
public:
	Sprite(
		std::shared_ptr<Texture> texture, 
		glm::vec2 position, 
		glm::vec2 size = glm::vec2(10.0f, 10.0f), 
		float rotate = 0.0f,
		glm::vec3 color = glm::vec3(1.0f));

	~Sprite() {};

	std::shared_ptr<Texture> m_Texture;
	glm::vec2 position;
	glm::vec2 size;
	float rotation;
	glm::vec3 color;
private:
};