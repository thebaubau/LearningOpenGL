#pragma once

#include <memory>
#include <glm/glm.hpp>

#include "GameObject.h"
#include "Texture.h"

class BallObject : public GameObject
{
public:
	float radius;
	bool stuck;

	BallObject();
	BallObject(glm::vec2 pos, float radius, std::shared_ptr<Texture> sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));

	glm::vec2 Move(float deltaTime, unsigned int winwowWidth);
	void Reset(glm::vec2 position, glm::vec2 velocity);
};

