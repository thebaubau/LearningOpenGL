#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <Texture.h>
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"

class SpriteRenderer
{
public:
	SpriteRenderer(Shader& shader);
	~SpriteRenderer();

	void DrawSprite(Texture& texture, glm::vec2 position,
		glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f,
		glm::vec3 color = glm::vec3(1.0f));

	Shader& m_Shader;
private:
	std::unique_ptr<VertexArray> m_VAO;
	std::unique_ptr<VertexBuffer> m_VBO;
	std::unique_ptr<IndexBuffer> m_EBO;

	void InitRenderData();
};

