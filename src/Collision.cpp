#include "Collision.h"

Collision::Direction Collision::VectorDirection(glm::vec2 target)
{
	glm::vec2 compass[] = {
		glm::vec2(0.0f, 1.0f),	// up
		glm::vec2(1.0f, 0.0f),	// right
		glm::vec2(0.0f, -1.0f),	// down
		glm::vec2(-1.0f, 0.0f)	// left
	};
	float max = 0.0f;
	unsigned int best_match = -1;
	for (unsigned int i = 0; i < 4; i++)
	{
		float dot_product = glm::dot(glm::normalize(target), compass[i]);
		if (dot_product > max)
		{
			max = dot_product;
			best_match = i;
		}
	}
	return (Collision::Direction)best_match;
}

bool Collision::CheckCollision(GameObject& one, GameObject& two)
{
	// collision x-axis?
	bool collisionX = one.position.x + one.size.x >= two.position.x &&
		two.position.x + two.size.x >= one.position.x;
	// collision y-axis?
	bool collisionY = one.position.y + one.size.y >= two.position.y &&
		two.position.y + two.size.y >= one.position.y;
	// collision only if on both axes
	return collisionX && collisionY;
}

Collision::Collided Collision::CheckCollision(BallObject& one, GameObject& two) // AABB - Circle collision
{
	// get center point circle first 
	glm::vec2 center(one.position + one.radius);
	// calculate AABB info (center, half-extents)
	glm::vec2 aabb_half_extents(two.size.x / 2.0f, two.size.y / 2.0f);
	glm::vec2 aabb_center(
		two.position.x + aabb_half_extents.x,
		two.position.y + aabb_half_extents.y
	);
	// get difference vector between both centers
	glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
	// add clamped value to AABB_center and we get the value of box closest to circle
	glm::vec2 closest = aabb_center + clamped;
	// retrieve vector between center circle and closest point AABB and check if length <= radius
	difference = closest - center;
	if (glm::length(difference) <= one.radius)
		return std::make_tuple(true, Collision::VectorDirection(difference), difference);
	else
		return std::make_tuple(false, UP, glm::vec2(0.0f, 0.0f));
}