#pragma once
#include <string>
#include <glm.hpp>


class Material
{
public:
	std::string name;
	int diffuse;
	int specular;
	float shininess;
	glm::vec3 color;
};

