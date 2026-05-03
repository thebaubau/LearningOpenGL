#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator(std::shared_ptr<Texture> particleTexture, Shader& particleShader, unsigned int nrParticles) 
    : particleTexture(particleTexture), particleShader(particleShader), nrParticles(nrParticles)
{
    float particleQuad[] = {
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    vao = std::make_unique<VertexArray>();
    vbo = std::make_unique<VertexBuffer>(particleQuad, sizeof(particleQuad));
    layout = std::make_unique<VertexBufferLayout>();

    layout->Push<float>(2, 0); // Pos
    layout->Push<float>(2, 0); // Texture

    vao->AddBuffer(*vbo, *layout);

	for (int i{ 0 }; i < nrParticles; ++i) {
		particles.push_back(Particle());
	}
}

unsigned int ParticleGenerator::FirstUnusedParticle()
{
    // search from last used particle, this will usually return almost instantly
    for (unsigned int i = lastUsedParticle; i < nrParticles; ++i) {
        if (particles[i].Life <= 0.0f) {
            lastUsedParticle = i;
            return i;
        }
    }
    // otherwise, do a linear search
    for (unsigned int i = 0; i < lastUsedParticle; ++i) {
        if (particles[i].Life <= 0.0f) {
            lastUsedParticle = i;
            return i;
        }
    }
    // override first particle if all others are alive
    lastUsedParticle = 0;
    return 0;
}

void ParticleGenerator::RespawnParticle(Particle& particle, GameObject& object, glm::vec2 offset)
{
    float random = ((rand() % 100) - 50) / 10.0f;
    float rColor = 0.5f + ((rand() % 100) / 100.0f);
    particle.Position = object.position + random + offset;
    particle.Color = glm::vec4(rColor, rColor, rColor, 1.0f);
    particle.Life = 1.0f;
    particle.Velocity = object.velocity * 0.1f;
}

void ParticleGenerator::Update(float deltaTime, GameObject& object, unsigned int newParticles, glm::vec2 offset = glm::vec2(0.0f, 0.0f))
{
    for (unsigned int i = 0; i < nrNewParticles; ++i)
    {
        int unusedParticle = FirstUnusedParticle();
        RespawnParticle(particles[unusedParticle], object, offset);
    }
    // update all particles
    for (unsigned int i = 0; i < nrParticles; ++i)
    {
        Particle& p = particles[i];
        p.Life -= deltaTime; // reduce life
        if (p.Life > 0.0f)
        {	// particle is alive, thus update
            p.Position -= p.Velocity * deltaTime;
            p.Color.a -= deltaTime * 2.5f;
        }
    }
}

void ParticleGenerator::Draw()
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    particleShader.Bind();

    for (const Particle& particle : this->particles)
    {
        if (particle.Life > 0.0f)
        {
            this->particleShader.SetVec2("offset", particle.Position);
            this->particleShader.SetVec4("color", particle.Color);
            this->particleTexture->Bind();
            
            vao->Bind();
            Renderer renderer;
            renderer.Draw(*vao, particleShader, 6);
            vao->Unbind();
        }
    }
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
