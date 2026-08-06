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
	int fileSize = 0;
	int terrainSize = 0;
	float heightMap[256];

	float TerrainX, TerrainZ;

	void Render();
	float GetHeightInterporlated(float x, float z);
	
};

// How would I get the x, y, z values from the terrain and translate it into the world space.
