#include "Sprite.h"

Sprite::Sprite(std::shared_ptr<Texture> texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color)
	: m_Texture(texture), spriteData(position, size, rotate, color)
{
	setupSprite();
}

void Sprite::Draw(Shader& shader)
{
    
}

void Sprite::setupSprite()
{
    float vertices[] = {
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    m_VAO = std::make_unique<VertexArray>();
    m_VBO = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));

    VertexBufferLayout layout;

    layout.Push<float>(2, 0); // Pos
    layout.Push<float>(2, 0); // Tex coords

    m_VAO->AddBuffer(*m_VBO, layout);
}
