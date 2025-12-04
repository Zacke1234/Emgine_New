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




Mesh* MeshManager::LoadMesh(std::string objPath, std::string name)
{
	size_t fileSize = std::filesystem::file_size(objPath);
	std::string BinaryPath = "resource\\bins\\" + name + ".bin";
	Mesh* mesh = new Mesh;
	mesh->name = name;
	
	std::ofstream writeBin(BinaryPath, std::ios_base::binary); 
	std::ifstream readObj(objPath);
	std::ifstream readBin(BinaryPath, std::ios::binary);
	
	meshLoader->ReadObjToBinary(objPath, readObj, writeBin, mesh);
	if (meshLoader->WriteObjToBinary(readObj, writeBin, objPath, mesh))
	{
		
		meshLoader->BinParser(BinaryPath, mesh);
	}
	else
	{

		meshLoader->ObjParser(objPath, mesh);
		mesh->InitialiseMesh();

	}
	
	//check if binary path has file:
		//if file exists
			// parse binary->mesh
		//else
			// parse obj to binary
			// then binary ->mesh
		// then load mesh(instantiate) into meshmanager n stuff 

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

