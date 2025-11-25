#include "MeshManager.h"
#include <cassert>



#pragma once

MeshManager::MeshManager()
{
	meshLoader = new MeshLoader();
	//std::cout << "Client triggers operation 1 (meshManager)" << "\n";
}

MeshManager::~MeshManager()
{ 
	for (auto& [key, value] : MeshCache)
	{
		delete value;
	}
	delete meshLoader;
}




Mesh* MeshManager::LoadMesh(std::string fromPath, std::string name)
{
	size_t fileSize = std::filesystem::file_size(fromPath);
	std::string Binary = "resource\\bins\\" + name + ".bin";
	Mesh* mesh = new Mesh;
	mesh->name = name;
	//char* data = new char;
	//
	std::ofstream write("resource\\bins\\" + name + ".bin", std::ios::binary); // ./out.bin
	std::fstream read(fromPath);
	std::fstream readBin("resource\\bins\\" + name + ".bin");
	
	//meshLoader->DoMeshloadingStages(this, fromPath, "", read, write, readBin, Binary);
	
	
	if (meshLoader->ParseBinary(Binary, readBin, write, mesh))
	{
		meshLoader->WriteToBinary(read, write, fromPath, mesh);
		meshLoader->ObjParser(Binary, mesh, NULL);
	}
	else
	{
		meshLoader->ObjParser(fromPath, mesh);
	}
	
	mesh->InitialiseMesh();
	
	return mesh;
}	

Mesh* MeshManager::Create(std::string name, std::string path_end)
{
	std::string path = "resource\\meshes\\";
	Mesh* mesh = new Mesh();
	mesh->name = name;
	mesh = LoadMesh((path + path_end).c_str(), name);
	std::cout << "Mesh loaded in: " << name << " from path: " << path + path_end << "\n";
	MeshCache.emplace(name, mesh);
	std::cout << "Mesh created: " << name << " from path: " << path + path_end << "\n";
	
	
	return mesh;
}

