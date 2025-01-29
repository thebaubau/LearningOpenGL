#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

glm::mat4 LookAt(glm::vec3 cameraPos, glm::vec3 target, glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f))
{
	glm::vec3 zaxis = glm::normalize(cameraPos - target);
	glm::vec3 xaxis = glm::normalize(glm::cross(glm::normalize(up), zaxis));
	glm::vec3 yaxis = glm::cross(zaxis, xaxis);

	glm::mat4 translation = glm::mat4(1.0f);
	glm::mat4 rotation = glm::mat4(1.0f);

	translation = glm::translate(translation, -cameraPos);
	rotation[0][0] = xaxis.x;
	rotation[1][0] = xaxis.y;
	rotation[2][0] = xaxis.z;
	rotation[0][1] = yaxis.x;
	rotation[1][1] = yaxis.y;
	rotation[2][1] = yaxis.z;
	rotation[0][2] = zaxis.x;
	rotation[1][2] = zaxis.y;
	rotation[2][2] = zaxis.z;

	return rotation * translation;
};
