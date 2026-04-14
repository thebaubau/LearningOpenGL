#include "Sprite.h"
#include <glm/gtc/matrix_transform.hpp>

Sprite::Sprite(
    std::shared_ptr<Texture> texture, 
    glm::vec2 position, 
    glm::vec2 size, 
    float rotation, 
    glm::vec3 color)
	: m_Texture(texture), spriteData(position, size, rotation, color)
{
	SetupSprite();
}

void Sprite::Draw(Shader& shader)
{
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 projection = glm::ortho(0.0f, 1280.0f, 820.0f, 0.0f, -1.0f, 1.0f);

    model = glm::translate(model, glm::vec3(spriteData.Position, 0.0f));

    model = glm::translate(model, glm::vec3(0.5f * spriteData.Size.x, 0.5f * spriteData.Size.y, 0.0f));
    model = glm::rotate(model, glm::radians(spriteData.Rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * spriteData.Size.x, -0.5f * spriteData.Size.y, 0.0f));

    model = glm::scale(model, glm::vec3(spriteData.Size, 1.0f));

    shader.SetMat4("projection", projection);
    shader.SetMat4("model", model);
    shader.SetVec3("spriteColor", spriteData.Color);

    m_Texture->Bind();
    m_VAO->Bind();
    Renderer renderer;
    renderer.Draw(*m_VAO, shader, 6);
    m_VAO->Unbind();
}

void Sprite::SetupSprite()
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
