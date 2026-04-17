#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(Shader& shader)
	: m_Shader(shader)
{
	InitRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::DrawSprite(Texture& texture, glm::vec2 position, glm::vec2 size, float rotation, glm::vec3 color)
{
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

    model = glm::scale(model, glm::vec3(size, 1.0f));

    m_Shader.SetMat4("model", model);
    m_Shader.SetVec3("spriteColor", color);

    texture.Bind();
    m_VAO->Bind();
    Renderer renderer;
    renderer.Draw(*m_VAO, m_Shader, 6);
    m_VAO->Unbind();
}

void SpriteRenderer::InitRenderData()
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
