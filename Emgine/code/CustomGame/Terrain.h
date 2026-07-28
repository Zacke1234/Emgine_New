#pragma once
#include <vector>
#include "MeshManager.h"
struct Mesh;
class Terrain
{
public:

	Terrain();

	~Terrain();

	Mesh* terrainMesh;

	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	int width, height, channels;

	unsigned int NUM_STRIPS;
	unsigned int NUM_VERTS_PER_STRIP;
	

	void Render();
};

