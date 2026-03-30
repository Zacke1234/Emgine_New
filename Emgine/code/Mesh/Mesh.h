#pragma once
#include <string>
#include <vector>
#include "glm.hpp"
#include "Structs/Face.h"
#include "Structs/Vertex.h"

class Mesh
{
public:
	std::string name;

	int vertexbuffer = 0;
	unsigned int numberVertices = 0;
	unsigned int VAO = 0;
	unsigned int VBO = 0;
	unsigned int EBO = 0;

	size_t indexCount = 0, vertexCount = 0;

	std::vector<glm::vec3> position;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;
	std::vector<Vertex> vertices;
	std::vector<Face> faces;
	std::vector<float> data;
	std::vector<unsigned int> elements;

	void InitialiseMesh();

};

