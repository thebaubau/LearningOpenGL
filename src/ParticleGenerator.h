#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "GameObject.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"

struct Particle {
    glm::vec2 Position, Velocity;
    glm::vec4 Color;
    float     Life;

    Particle()
        : Position(0.0f), Velocity(0.0f), Color(1.0f), Life(0.0f) {}
};

class ParticleGenerator
{
public:
    ParticleGenerator(std::shared_ptr<Texture> particleTexture, Shader& particleShader, unsigned int nrParticles);
    ~ParticleGenerator() = default;

    void Update(float deltaTime, GameObject& object, unsigned int newParticles, glm::vec2 offset);
    void Draw();

    unsigned int nrParticles = 500;
    unsigned int nrNewParticles = 2;
    unsigned int lastUsedParticle = 0;
    std::vector<Particle> particles;

private:
    unsigned int FirstUnusedParticle();
    void RespawnParticle(Particle& particle, GameObject& object, glm::vec2 offset);

    Shader& particleShader;
    std::shared_ptr<Texture> particleTexture;
    std::unique_ptr<VertexArray> vao;
    std::unique_ptr<VertexBuffer> vbo;
    std::unique_ptr<VertexBufferLayout> layout;
};
