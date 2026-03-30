#pragma once
#include "glm.hpp"
struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal = glm::vec3(0, 0, 1);
	glm::vec2 uv;
};

