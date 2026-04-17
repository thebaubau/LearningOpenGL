#include "GameObject.h"

GameObject::GameObject()
    : position(0.0f, 0.0f), size(1.0f, 1.0f), velocity(0.0f), color(1.0f), rotation(0.0f), sprite(nullptr), isSolid(false), destroyed(false) {}

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, std::shared_ptr<Texture> sprite, glm::vec3 color, glm::vec2 velocity)
    : position(pos), size(size), velocity(velocity), color(color), rotation(0.0f), sprite(std::move(sprite)), isSolid(false), destroyed(false) {}

void GameObject::Draw(SpriteRenderer& renderer)
{
    renderer.DrawSprite(*this->sprite, this->position, this->size, this->rotation, this->color);
}