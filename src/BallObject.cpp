#include "BallObject.h"

BallObject::BallObject() 
    : GameObject(), radius(12.5f), stuck(true) {}

BallObject::BallObject(glm::vec2 pos, float radius, std::shared_ptr<Texture> sprite, glm::vec3 color, glm::vec2 velocity)
    : GameObject(pos, glm::vec2(radius * 2.0f, radius * 2.0f), sprite, color, velocity), radius(radius), stuck(true) {}

glm::vec2 BallObject::Move(float deltaTime, unsigned int windowWidth) {
	if (!this->stuck) {
		this->position += this->velocity * deltaTime;

		if (this->position.x <= 0.0f) {
			this->position.x = 0.0f;
			this->velocity.x = -this->velocity.x;
		}

        else if (this->position.x + this->size.x >= windowWidth)
        {
            this->velocity.x = -this->velocity.x;
            this->position.x = windowWidth - this->size.x;
        }
        if (this->position.y <= 0.0f)
        {
            this->velocity.y = -this->velocity.y;
            this->position.y = 0.0f;
        }
	}
    return this->position;
}

void BallObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
    this->position = position;
    this->velocity = velocity;
    this->stuck = true;
}