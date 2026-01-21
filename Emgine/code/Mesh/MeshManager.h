#pragma once
#include "MeshLoader.h"
#include <string>
#include "vector"
#include <filesystem>
#include <Message.h>
#include <map>
#include "Cube.h"
class MeshLoader;
class Cube;

class MeshManager : public Observer
{
	
	MeshLoader* meshLoader = nullptr;
public:
	//Constructor and Destructor
	MeshManager();
	~MeshManager();



	void Update(std::string message_from_subject) override {
		std::cout << "MeshManager received message: " << message_from_subject << "\n";
	};

	std::string msg;

	// Mesh Management
	static std::vector<Mesh> MeshCache;
	static std::vector<std::string> MeshList;
	Mesh* LoadMesh(std::string fromPath, std::string name, Mesh* mesh);
	Mesh* LoadFromMeshCache(std::string fromPath, std::string name, Mesh* mesh);
	Mesh* Create(std::string name = "newmesh", std::string path_end = NULL);
	
};


