#pragma once
#include "GameObject.h"

class PowerUp : public GameObject
{
public:
    
    std::string Type;
    float Duration;
    bool Activated;

    inline static const glm::vec2 SIZE{60.0f, 20.0f};
    inline static const glm::vec2 VELOCITY{0.0f, 150.0f};

    
    PowerUp(std::string type, glm::vec3 color, float duration,
        glm::vec2 position, std::shared_ptr<Texture> texture)
        : GameObject(position, SIZE, texture, color, VELOCITY),
        Type(type), Duration(duration), Activated(false)
    {}

};

