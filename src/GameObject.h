#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Texture.h"
#include "SpriteRenderer.h"

// Container object for holding all state relevant for a single
// game object entity. Each object in the game likely needs the
// minimal of state as described within GameObject.
class GameObject
{
public:
    GameObject();
    GameObject(glm::vec2 pos, glm::vec2 size, std::shared_ptr<Texture> sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));

    glm::vec2   position, size, velocity;
    glm::vec3   color;
    float       rotation;
    bool        isSolid;
    bool        destroyed;
    std::shared_ptr<Texture> sprite;

    virtual void Draw(SpriteRenderer& renderer);
};
