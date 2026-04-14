#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <Texture.h>
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"

struct SpriteData {
	glm::vec2 Position;
	glm::vec2 Size;
	float Rotation;
	glm::vec3 Color;
};

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

	SpriteData spriteData;

	std::shared_ptr<Texture> m_Texture;
	std::unique_ptr<VertexArray> m_VAO;

	void Draw(class Shader& shader);

private:
	std::unique_ptr<VertexBuffer> m_VBO;
	std::unique_ptr<IndexBuffer> m_EBO;

	void SetupSprite();
};