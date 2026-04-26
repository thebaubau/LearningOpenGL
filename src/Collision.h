#pragma once
#include "GameObject.h"
#include "BallObject.h"
#include <tuple>

namespace Collision
{
	enum Direction {
		UP,
		RIGHT,
		DOWN,
		LEFT
	};

	typedef std::tuple<bool, Direction, glm::vec2> Collided;

	bool CheckCollision(GameObject& one, GameObject& two);
	Collided CheckCollision(BallObject& one, GameObject& two);
	Direction VectorDirection(glm::vec2 target);
}

