#include "Sprite.h"

Sprite::Sprite(
    std::shared_ptr<Texture> texture, 
    glm::vec2 position, 
    glm::vec2 size, 
    float rotation, 
    glm::vec3 color)
	: m_Texture(texture), position(position), size(size), rotation(rotation), color(color)
{
}

